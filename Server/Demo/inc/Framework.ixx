export module Demo.Framework;
import Iconer.Declarations;
import Iconer.Utility.Logger;
import Iconer.Network.UserManager;
export import Iconer.Network.User;
import Net.Constraints;
import Net.Socket;
import Net.Io.Context;
import <cstdint>;
import <vector>;
import <thread>;

export namespace demo
{
	class [[nodiscard]] Framework final
	{
	public:
		static inline constexpr iconer::user_id_t startUserID = 1000;
		static inline size_t workersCount = std::thread::hardware_concurrency();

		Framework(size_t clients_count, std::uint16_t port);
		~Framework() = default;

		void Awake();
		void Start();
		void Update();
		void Cleanup() noexcept;

		friend void Worker(Framework& framework, std::stop_token&& token);

	private:
		static iconer::util::Logger serverLogger;

		Framework(const Framework&) = delete;
		Framework(Framework&&) = delete;
		void operator=(const Framework&) = delete;
		void operator=(Framework&&) = delete;

		std::vector<std::jthread*> serverWorkers;
		std::stop_source workerCanceller;
		net::Socket listenSocket;
		net::io::Context listenContext;
		iconer::UserManager everyUsers;
		std::stop_source cancellationSource;
	};

	void Worker(Framework& framework, std::stop_token&& token);
}