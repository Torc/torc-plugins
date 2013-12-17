TEMPLATE = subdirs
CONFIG  += ordered

#check QT major version
lessThan(QT_MAJOR_VERSION, 5) {
    error("Must build against Qt5")
}




