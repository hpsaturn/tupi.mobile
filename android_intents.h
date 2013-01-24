#ifndef ANDROID_INTENTS_H
#define ANDROID_INTENTS_H

#include <jni.h>
#include <QString>

class AndroidIntents
{
public:
    AndroidIntents();
    ~AndroidIntents();
    bool setUrl(const QString &url);


private:
    jobject m_intentObject;

};

#endif // ANDROID_INTENTS_H
