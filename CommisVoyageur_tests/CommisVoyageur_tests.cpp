#define CATCH_CONFIG_MAIN
#include "../CommisVoyageur/CommisVoyageur.h"
#include "../catch2/catch.hpp"
#include <boost/timer.hpp>

//TEST_CASE("Test with N = 10")
//{
//	boost::timer t;
//	t.restart();
//	Matrix roads = {
//		{ 0, 12, 13, 14, 15, 16, 17, 18, 19, 110 },
//		{ 12, 0, 23, 24, 25, 26, 27, 28, 29, 210 },
//		{ 13, 23, 0, 34, 35, 36, 37, 38, 39, 310 },
//		{ 14, 24, 34, 0, 45, 46, 47, 48, 49, 410 },
//		{ 15, 25, 35, 45, 0, 56, 57, 58, 59, 510 },
//		{ 16, 26, 36, 46, 56, 0, 67, 68, 69, 610 },
//		{ 17, 27, 37, 47, 57, 67, 0, 78, 79, 710 },
//		{ 18, 28, 38, 48, 58, 68, 78, 0, 89, 810 },
//		{ 19, 29, 39, 49, 59, 69, 79, 89, 0, 910 },
//		{ 110, 210, 310, 410, 510, 610, 710, 810, 910, 0 }
//	};
//
//	// Matrix roads = {
//	//{0, 12, 700, 3},
//	//{12, 0, 5, 100},
//	//{700, 5, 0, 4},
//	//{3, 100, 4, 0}
//	// };
//	CommisVoyageur counter(roads);
//	std::vector<size_t> bestPermutation = counter.CountBestPermutation();
//	std::vector<size_t> expectedPermutation = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//	double duration = t.elapsed();
//	std::cout << duration << std::endl;
//	REQUIRE(bestPermutation == expectedPermutation);
//}

//TEST_CASE("Test with N = 15")
//{
//	boost::timer t;
//	t.restart();
//	Matrix roads = {
//		{ 0, 12, 13, 14, 15, 16, 17, 18, 19, 110, 111, 112, 113, 114, 115 },
//		{ 12, 0, 23, 24, 25, 26, 27, 28, 29, 210, 211, 212, 213, 214, 215 },
//		{ 13, 23, 0, 34, 35, 36, 37, 38, 39, 310, 311, 312, 313, 314, 315 },
//		{ 14, 24, 34, 0, 45, 46, 47, 48, 49, 410, 411, 412, 413, 414, 415 },
//		{ 15, 25, 35, 45, 0, 56, 57, 58, 59, 510, 511, 512, 513, 514, 515 },
//		{ 16, 26, 36, 46, 56, 0, 67, 68, 69, 610, 611, 612, 613, 614, 615 },
//		{ 17, 27, 37, 47, 57, 67, 0, 78, 79, 710, 711, 712, 713, 714, 715 },
//		{ 18, 28, 38, 48, 58, 68, 78, 0, 89, 810, 811, 812, 813, 814, 815 },
//		{ 19, 29, 39, 49, 59, 69, 79, 89, 0, 910, 911, 912, 913, 914, 915 },
//		{ 110, 210, 310, 410, 510, 610, 710, 810, 910, 0, 1011, 1012, 1013, 1014, 1015 },
//		{ 111, 211, 311, 411, 511, 611, 711, 811, 911, 1011, 0, 1112, 1113, 1114, 1115 },
//		{ 112, 212, 312, 412, 512, 612, 712, 812, 912, 1012, 1112, 0, 1213, 1214, 1215 },
//		{ 113, 213, 313, 413, 513, 613, 713, 813, 913, 1013, 1113, 1213, 0, 1314, 1315 },
//		{ 114, 214, 314, 414, 514, 614, 714, 814, 914, 1014, 1114, 1214, 1314, 0, 1415 },
//		{ 115, 215, 315, 415, 515, 615, 715, 815, 915, 1015, 1115, 1215, 1315, 1415, 0 }
//	};
//
//	// Matrix roads = {
//	//{0, 12, 700, 3},
//	//{12, 0, 5, 100},
//	//{700, 5, 0, 4},
//	//{3, 100, 4, 0}
//	// };
//	CommisVoyageur counter(roads);
//	std::vector<size_t> bestPermutation = counter.CountBestPermutation();
//	std::vector<size_t> expectedPermutation = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
//	double duration = t.elapsed();
//	std::cout << duration << std::endl;
//	REQUIRE(bestPermutation == expectedPermutation);
//}

//TEST_CASE("Empty graph")
//{
//	boost::timer t;
//	t.restart();
//	Matrix roads = {
//		{ 0, 0, 0, 0 },
//		{ 0, 0, 0, 0 },
//		{ 0, 0, 0, 0 },
//		{ 0, 0, 0, 0 }
//	};
//
//	// Matrix roads = {
//	//{0, 12, 700, 3},
//	//{12, 0, 5, 100},
//	//{700, 5, 0, 4},
//	//{3, 100, 4, 0}
//	// };
//	CommisVoyageur counter(roads);
//	std::vector<size_t> bestPermutation = counter.CountBestPermutation();
//	std::vector<size_t> expectedPermutation = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//	double duration = t.elapsed();
//	std::cout << duration << std::endl;
//	REQUIRE(bestPermutation == expectedPermutation);
//}