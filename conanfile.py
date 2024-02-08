from conan import ConanFile


class Project(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def configure(self):
        self.options["boost"].header_only = True

    def requirements(self):
        self.requires("boost/1.84.0")
