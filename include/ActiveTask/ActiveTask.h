#pragma once

#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <functional>
#include <atomic>

class ActiveTask
{

public:
	//copy and move ops are forbidden
	ActiveTask(const ActiveTask&) = delete;
	ActiveTask(ActiveTask&&) = delete;
	ActiveTask& operator=(const ActiveTask&) = delete;
	ActiveTask& operator=(ActiveTask&&) = delete;
	virtual ~ActiveTask()
	{
		alive = false;
		cv.notify_one();
		if (thr.joinable())
		{
			thr.join();
		}
	}

protected:
	ActiveTask()
	{
		thr = std::thread([&]() {
			while (alive)
			{
				std::unique_lock<std::mutex> ul(mtx);
				cv.wait(ul, [&]() {return ((!queWork.empty()) || (!alive)); });
				if (!alive)
				{
					ul.unlock();
					break;
				}
				std::function<void()> func = queWork.front();
				//std::invoke(func);
				func();
				queWork.pop();
				ul.unlock();
			}
		});
	}

	

	template<typename Function, typename... Arguments>
	void ExecuteOnMyTask(Function funcToBind, Arguments... paramsToBind)
	{
		{
			const std::function<void()> funcToCall{ std::bind(funcToBind, paramsToBind...) };
			
			std::lock_guard<std::mutex> lk(mtx);
			queWork.push(funcToCall);
		}
		cv.notify_one();			//notifying doesn't require thread-safety
	}

	size_t GetMyWorkCount()
	{
		size_t workCount = 0;
		{
			std::lock_guard<std::mutex> lk(mtx);
			workCount = queWork.size();
		}
		return workCount;
	}
	
	//[[nodiscard]]
	std::thread::id GetMyTaskID() const noexcept
	{
		return thr.get_id();
	}

private:
	std::atomic<bool> alive{true};
	std::mutex mtx;
	std::condition_variable cv;
	std::queue<std::function<void()>> queWork;
	std::thread thr;
};

