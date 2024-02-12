export module Iconer.Utility.D3D.Transform:Quark;

export namespace iconer::util::d3d
{
	struct [[nodiscard]] Matrix final
	{
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;
	};

	struct [[nodiscard]] Position final
	{
		float x, y, z;
	};

	struct [[nodiscard]] Quaternion final
	{
		float x, y, z, w;
	};
}
