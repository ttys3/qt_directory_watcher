// ----------------------------------------------
// List the contents of a directory if changed
// Using QFileSystemWatcher, QDirIterator and
// QEventLoop, and lambda function for connect
// ----------------------------------------------

#include <QApplication>
#include <QObject>
#include <QEventLoop>
#include <QDebug>
#include <QFileSystemWatcher>
#include <QDirIterator>

void listDirectoryContents( const QString& dir ) noexcept
{
    QFileSystemWatcher watcher;
    watcher.addPath( dir );

    QEventLoop loop;
    
    QObject::connect( &watcher, &QFileSystemWatcher::directoryChanged,
                      []( const QString& path )
    {
        qDebug() << "\n----------------------------------------------------------";

        QDirIterator it( path,
                        { "*.torrent" },        // Filter: *.torrent
                        QDir::Files );   // Files only

        while ( it.hasNext() )              // List all txt files
        {                                   // on console
            qDebug() << it.next();
        }
    });
    
    // QObject::connect( &watcher, &QFileSystemWatcher::directoryChanged, &loop, &QEventLoop::quit );
    
    loop.exec();
}

// Example

int main(int argc, char** argv)
{
    if (argc != 2) {
        qDebug() << "usage: " << *argv <<  "path";
        return -1;
    }
    QCoreApplication app(argc, argv);
    const QString dir { *(argv+1) };
    listDirectoryContents( dir );
    app.exec();
    return 0;
}