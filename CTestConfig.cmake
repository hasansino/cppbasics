# https://cmake.org/cmake/help/latest/guide/tutorial/Adding%20Support%20for%20a%20Testing%20Dashboard.html
# https://my.cdash.org/index.php?project=CMakeTutorial
set(CTEST_PROJECT_NAME "CMakeTutorial")
set(CTEST_NIGHTLY_START_TIME "00:00:00 UTC")
set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "my.cdash.org")
set(CTEST_DROP_LOCATION "/submit.php?project=CMakeTutorial")
set(CTEST_DROP_SITE_CDASH TRUE)