function(update_git_submodule submodule_dir)
# add a Git submodule directory to CMake, assuming the
# Git submodule directory is a CMake project.
#
# Usage: in CMakeLists.txt
#
# include(AddGitSubmodule.cmake)
# update_git_submodule(mysubmod_dir)
find_package(Git QUIET)
    if(GIT_FOUND)
        if(NOT EXISTS ${submodule_dir}/CMakeLists.txt)
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive -- ${submodule_dir}
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                RESULT_VARIABLE RETURN_CODE)
            if(NOT RETURN_CODE EQUAL "0")
                message(WARNING "Cannot update ${submodule_dir}. Git command failed with ${RETURN_CODE}")
                return()
            endif()
            message(STATUS "Git submodules updated successfully")
        endif()
    endif()
endfunction(update_git_submodule)
