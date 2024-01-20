export module Net.Coroutine.Promissory;
import Net.Coroutine.Suspender;

export namespace net::coroutine
{
	template<typename P>
	concept Promissory = requires(P object)
	{
		object.get_return_object();
		{ object.initial_suspend() } -> Suspender;
		{ object.final_suspend() } -> Suspender;
	};
}
