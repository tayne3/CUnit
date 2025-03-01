
include(FindGit)

set(CUNIT_VERSION_MAJOR 0)
set(CUNIT_VERSION_MINOR 0)
set(CUNIT_VERSION_PATCH 0)

if(GIT_FOUND)
    execute_process(
        COMMAND
            ${GIT_EXECUTABLE} describe --abbrev=0 --tags --always
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE
            GITRET
        OUTPUT_VARIABLE
            GIT_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

	if(GIT_VERSION)
		string(REGEX REPLACE "^v([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\1" CUNIT_VERSION_MAJOR "${GIT_VERSION}")
		string(REGEX REPLACE "^v([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\2" CUNIT_VERSION_MINOR "${GIT_VERSION}")
		string(REGEX REPLACE "^v([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\3" CUNIT_VERSION_PATCH "${GIT_VERSION}")
	endif()
endif()

set(CUNIT_VERSION "${CUNIT_VERSION_MAJOR}.${CUNIT_VERSION_MINOR}.${CUNIT_VERSION_PATCH}")
