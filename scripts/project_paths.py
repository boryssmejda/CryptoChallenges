import os

SCRIPTS_LOCATION = os.getcwd() # PROJECT_ROOT/scripts/
PROJECT_ROOT = os.path.dirname(SCRIPTS_LOCATION)
BUILD_DIR = os.path.join(PROJECT_ROOT, "build")
INSTALL_DIR = os.path.join(PROJECT_ROOT, "install")

CONAN_FOLDER_LOCATION = os.path.join(PROJECT_ROOT, "conan")
CONANFILE_DESKTOP_LOCATION = os.path.join(CONAN_FOLDER_LOCATION, "conanfiles", "conanfile.txt")

CONAN_PROFILES_ROOT = os.path.join(CONAN_FOLDER_LOCATION, "profiles")
CONAN_PROFILE_LOCATION_LINUX = os.path.join(CONAN_PROFILES_ROOT, "conan-profile-linux.txt")

def print_project_paths():
    print("SCRIPTS_LOCATION: {}".format(SCRIPTS_LOCATION))
    print("PROJECT_ROOT: {}".format(PROJECT_ROOT))
    print("BUILD_DIR: {}".format(BUILD_DIR))
    print("INSTALL_DIR: {}".format(INSTALL_DIR))

    print("CONAN_FOLDER_LOCATION: {}".format(CONAN_FOLDER_LOCATION))
    print("CONANFILE_DESKTOP_LOCATION: {}".format(CONANFILE_DESKTOP_LOCATION))

    print("CONAN_PROFILES_ROOT: {}".format(CONAN_PROFILES_ROOT))
    print("CONAN_PROFILE_LOCATION_LINUX: {}".format(CONAN_PROFILE_LOCATION_LINUX))


if __name__ == "__main__":
    print_project_paths()