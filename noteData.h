
namespace tuning {
	template<typename Iterator> void generate_scale(Iterator it, const Iterator& end,
		int base_index = 60, int base_period = 3822, float tuning_constant = 1.05946309436);

	const float equal_tempered[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	const float pythagorean[12] = 
	{0, -0.0464, +0.0067, +0.0284, -.0260, -0.0040, -0.0207, +0.0044, +0.0330, -0.0394, +0.0477, -0.0333}; 
	const float test_tuning[12] = 
	{0, .5, -.5, 0, .5, -.5, 0, .5, -.5, 0, .5, -.5};

	template<typename Iterator> void generate_scale(Iterator it, const Iterator& end,
		const float offset[12],
		int base_index = 60, int base_period = 3822, float tuning_constant = 1.05946309436);
}