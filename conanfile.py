from conans import ConanFile, CMake, tools
from conans.errors import ConanInvalidConfiguration

class Pineapple(ConanFile):
    """ """
    name = "pineapple"
    version = "0.1.1"
    license = "Apache 2.0"
    author = "Martin Kvisvik Larsen"
    description = "Pineapple is a toolbox for remote control and real-time \
        visualization for sensors based on Pine."
    url = "https://github.com/markvilar/pineapple.git"
    homepage = "https://github.com/markvilar/pineapple.git"

    settings = "os", "compiler", "build_type", "arch"
    options = { "shared" : [True, False], "fPIC" : [True, False] }
    default_options = { "shared" : False, "fPIC" : True }

    generators = "cmake", "cmake_find_package"

    @property
    def _source_subfolder(self):
        return "source_subfolder"

    @property
    def _build_subfolder(self):
        return "build_subfolder"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        """ Configures project settings. """
        if self.options.shared:
            del self.options.fPIC

    def requirements(self):
        """ Specifies the requirements of the package. """
        self.requires("pine/0.3")
        self.requires("msgpack/3.3.0")

    def validate(self):
        """ Validates the project configuration. """
        if self.settings.compiler == "clang":
            if tools.Version(self.settings.compiler.version) < "8":
                raise ConanInvalidConfiguration("Invalid clang compiler \
                    version.")
        if self.settings.compiler == "gcc":
            if tools.Version(self.settings.compiler.version) < "7":
                raise ConanInvalidConfiguration("Invalid gcc compiler \
                    version.")
        if self.settings.compiler == "Visual Studio":
            if tools.Version(self.settings.compiler.version) < "16":
                raise ConanInvalidConfiguration("Invalid Visual Studio \
                    compiler version.")

    def _configure_cmake(self):
        """ Configure CMake. """
        cmake = CMake(self, generator="Ninja")
        cmake.definitions["ZED_LINK_SHARED"] = True
        cmake.definitions["PINEAPPLE_BUILD_EXAMPLES"] = True
        cmake.configure()
        return cmake

    def build(self):
        """ Builds the library. """
        cmake = self._configure_cmake()
        cmake.build()
