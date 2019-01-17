#include <thread>
#include <vector>


class CDetached {
public:
	CDetached() = default;
	~CDetached() {
		for (auto& t : m_threads) {
			t.join();
		}
	}


	CDetached(const CDetached&) = delete;
	CDetached& operator=(const CDetached&) = delete;

	template<typename FUNC, typename... Args>
	void creatDetachedThread(FUNC&& func, Args... args) {
		m_threads.emplace_back(std::forward<FUNC>(func), std::forward<Args>(args)...);
	}

private:
	std::vector<std::thread> m_threads;
};