export module Demo.Framework;
import Iconer.Declarations;
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

		Framework(size_t clients_count, std::uint16_t port);
		~Framework() = default;

		void Awake();
		bool Start() noexcept;
		void Update();
		void Cleanup() noexcept;

	private:
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
}
