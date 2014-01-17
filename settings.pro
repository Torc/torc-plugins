cache()

PROJECTNAME = torc
LIBVERSION  = 0.1
VERSION     = 0.1.0

#check QT major version
lessThan(QT_MAJOR_VERSION, 5) {
    error("Must build against Qt5")
}

# Where binaries, includes and runtime assets are installed by 'make install'
isEmpty(PREFIX) {
    PREFIX = /usr/local
}
# Where the binaries actually locate the assets/filters/plugins at runtime
isEmpty(RUNPREFIX) {
    RUNPREFIX = $$PREFIX
}
# Alternate library dir for OSes and packagers (e.g. lib64)
isEmpty(LIBDIRNAME) {
    LIBDIRNAME = lib
}
# Where libraries, plugins and filters are installed
isEmpty(LIBDIR) {
    LIBDIR = $${RUNPREFIX}/$${LIBDIRNAME}
}

DEFINES += _GNU_SOURCE

target.path = $${LIBDIR}/torc/plugins

LIBS += -ltorc-core-$$LIBVERSION
INCLUDEPATH += $${PREFIX}/include/torc
