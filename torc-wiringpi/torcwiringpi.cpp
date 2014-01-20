// Torc
#include "torclogging.h"
#include "torcadminthread.h"
#include "torcwiringpi.h"

// WiringPi
#include <wiringPi.h>
#include <softPwm.h>

TorcWiringPi* gTorcWiringPi = NULL;

#define PWM_RANGE 100

#define LEFT_PWM_PIN  0 // GPIO0 or Broadcom 17. This is the enable pin.
#define LEFT_INA_PIN  2 // GPIO2 or Broadcom 21/27.
#define LEFT_INB_PIN  3 // GPIO3 or Broadcom 22

#define RIGHT_PWM_PIN 6 // GPIO6 or Broadcom 25
#define RIGHT_INA_PIN 4 // GPIO4 or Broadcom 23
#define RIGHT_INB_PIN 5 // GPIO5 or Broadcom 24

bool LoadPlugin(const char* QtVersion)
{
    UnloadPlugin();

    if (QString::compare(QtVersion, QT_VERSION_STR) != 0)
    {
        LOG(VB_GENERAL, LOG_ERR, "Torc core was compiled with a different version of Qt");
        LOG(VB_GENERAL, LOG_ERR, QString("Core Qt version: %1 torc-wiringpi version: %2").arg(QtVersion).arg(QT_VERSION_STR));
        return false;
    }

    gTorcWiringPi = new TorcWiringPi();
    return true;
}

bool UnloadPlugin(void)
{
    delete gTorcWiringPi;
    gTorcWiringPi = NULL;
    return true;
}

TorcWiringPi::TorcWiringPi()
  : QObject(),
    TorcHTTPService(this, "wiringpi", "wiringpi", TorcWiringPi::staticMetaObject),
    speedLeft(0),
    speedRight(0)
{
    // initialise wiringPi
    wiringPiSetup();

    pinMode(LEFT_INA_PIN, OUTPUT);
    pinMode(LEFT_INB_PIN, OUTPUT);
    if (softPwmCreate(LEFT_PWM_PIN, 0, PWM_RANGE) != 0)
        LOG(VB_GENERAL, LOG_ERR, QString("Failed to create software PWM pin %1").arg(LEFT_PWM_PIN));

    pinMode(RIGHT_INA_PIN, OUTPUT);
    pinMode(RIGHT_INB_PIN, OUTPUT);
    if (softPwmCreate(RIGHT_PWM_PIN, 0, PWM_RANGE) != 0)
        LOG(VB_GENERAL, LOG_ERR, QString("Failed to create software PWM pin %1").arg(RIGHT_PWM_PIN));

    digitalWrite(LEFT_INA_PIN, 0);
    digitalWrite(LEFT_INB_PIN, 0);
    digitalWrite(RIGHT_INA_PIN, 0);
    digitalWrite(RIGHT_INB_PIN, 0);

    LOG(VB_GENERAL, LOG_INFO, "TorcWiringPi ready");
}

TorcWiringPi::~TorcWiringPi()
{
}

void TorcWiringPi::SubscriberDeleted(QObject *Subscriber)
{
    TorcHTTPService::HandleSubscriberDeleted(Subscriber);
}

int TorcWiringPi::GetSpeedLeft(void)
{
    return speedLeft;
}

int TorcWiringPi::GetSpeedRight(void)
{
    return speedRight;
}

void TorcWiringPi::SetSpeedLeft(int Speed)
{
    int speed = qBound(-PWM_RANGE, Speed, PWM_RANGE);

    if (speedLeft != speed)
    {
        speedLeft = speed;

        if (speedLeft < 0)
        {
            softPwmWrite(LEFT_PWM_PIN, -speedLeft);
            digitalWrite(LEFT_INA_PIN, 0);
            digitalWrite(LEFT_INB_PIN, 1);
        }
        else
        {
            softPwmWrite(LEFT_PWM_PIN, speedLeft);
            digitalWrite(LEFT_INA_PIN, 1);
            digitalWrite(LEFT_INB_PIN, 0);
        }
        emit SpeedLeftChanged(speedLeft);
    }
}

void TorcWiringPi::SetSpeedRight(int Speed)
{
    int speed = qBound(-PWM_RANGE, Speed, PWM_RANGE);

    if (speedRight != speed)
    {
        speedRight = speed;

        if (speedRight < 0)
        {
            softPwmWrite(RIGHT_PWM_PIN, -speedRight);
            digitalWrite(RIGHT_INA_PIN, 0);
            digitalWrite(RIGHT_INB_PIN, 1);
        }
        else
        {
            softPwmWrite(RIGHT_PWM_PIN, speedRight);
            digitalWrite(RIGHT_INA_PIN, 1);
            digitalWrite(RIGHT_INB_PIN, 0);
        }
        emit SpeedRightChanged(speedRight);
    }
}
