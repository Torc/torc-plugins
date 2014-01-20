#ifndef TORC_WIRINGPI_H
#define TORC_WIRINGPI_H

// Qt
#include <QObject>

// Torc
#include "torclocalcontext.h"
#include "torchttpservice.h"
#include "torcwiringpiexport.h"

extern "C" {
    bool TORC_WIRINGPI_PUBLIC LoadPlugin    (const char* QtVersion);
    bool TORC_WIRINGPI_PUBLIC UnloadPlugin  (void);
}

class TorcWiringPi : public QObject, public TorcHTTPService
{
    Q_OBJECT
    Q_CLASSINFO("Version",   "1.0.0")
    Q_PROPERTY(int speedLeft  READ GetSpeedLeft  WRITE SetSpeedLeft  NOTIFY SpeedLeftChanged)
    Q_PROPERTY(int speedRight READ GetSpeedRight WRITE SetSpeedRight NOTIFY SpeedRightChanged)

  public:
    TorcWiringPi             ();
    virtual ~TorcWiringPi    ();

  signals:
    void  SpeedLeftChanged   (int Speed);
    void  SpeedRightChanged  (int Speed);

  public slots:
    int   GetSpeedLeft       (void);
    int   GetSpeedRight      (void);
    void  SetSpeedLeft       (int Speed);
    void  SetSpeedRight      (int Speed);
    void  SubscriberDeleted  (QObject *Subscriber);

  private:
    int   speedLeft;
    int   speedRight;
};
#endif // TORC_WIRINGPI_H
