/***************************************************************************
 *   Project TUPI: Open 2D Magic                                           *
 *   Component: tupi.mobile                                                *
 *   Project Contact: info@maefloresta.com                                 *
 *   Project Website: http://www.maefloresta.com                           *
 *                                                                         *
 *   Developers:                                                           *
 *   2012:                                                                 *
 *    Gustavo Gonzalez / @xtingray                                         *
 *    Andres Calderon / @andresfcalderon                                   *
 *    Antonio Vanegas / @hpsaturn                                          *
 *                                                                         *
 *   License:                                                              *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#include "tupandroidintents.h"
#include <QDebug>

static JavaVM* s_javaVM = 0;
static jclass androidIntentClassID = 0;
static jmethodID constructorMethodID=0;
static jmethodID setUrlMethodID=0;
static jmethodID getMediaStorageMethodID=0;
static jmethodID getLastSaveMethodID=0;
static jmethodID setLastSaveMethodID=0;
static jmethodID getStringFromKeyID=0;
static jmethodID setStringByKeyID=0;


TupAndroidIntents::TupAndroidIntents()
{
    JNIEnv* env;
    // Qt is running in a different thread than Java UI, so you always Java VM *MUST* be attached to current thread
    if (s_javaVM->AttachCurrentThread(&env, NULL)<0) {
        qCritical()<<"AttachCurrentThread failed";
        return;
    }

    // Create a new instance of QSimpleAudioPlayer
    m_intentObject = env->NewGlobalRef(env->NewObject(androidIntentClassID, constructorMethodID));
    if (!m_intentObject) {
        qCritical()<<"Can't create the player";
        return;
    }

    // Don't forget to detach from current thread
    s_javaVM->DetachCurrentThread();
}

TupAndroidIntents::~TupAndroidIntents()
{
    if (!m_intentObject)return;

    JNIEnv* env;
    if (s_javaVM->AttachCurrentThread(&env, NULL) < 0) {
        qCritical()<<"AttachCurrentThread failed";
        return;
    }

    s_javaVM->DetachCurrentThread();
}

QString TupAndroidIntents::getLastFrameString()
{
    return getStringFromId(getLastSaveMethodID);
}

bool TupAndroidIntents::setLastFrameString(const QString &qstr)
{
    return setStringById(setLastSaveMethodID,qstr);
}

QString TupAndroidIntents::getStringFromKey(const QString &qkey)
{
    if (!m_intentObject)return 0;

    JNIEnv* env;
    if (s_javaVM->AttachCurrentThread(&env, NULL) < 0) {
        qCritical()<<"AttachCurrentThread failed";
        return 0;
    }

    jobject jsout  = env->CallObjectMethod(m_intentObject,getStringFromKeyID,qkey);
    const char *resultCStr = env->GetStringUTFChars((jstring)jsout, 0);

    QByteArray qbArry(resultCStr);
    QString str(qbArry);
    s_javaVM->DetachCurrentThread();

    return str;
}

bool TupAndroidIntents::setStringByKey(const QString &qkey,const QString &qdata)
{
    if (!m_intentObject)return false;

    JNIEnv* env;
    if (s_javaVM->AttachCurrentThread(&env, NULL) < 0) {
        qCritical()<<"AttachCurrentThread failed";
        return false;
    }

    jstring key = env->NewString(reinterpret_cast<const jchar*>(qkey.constData()), qkey.length());
    jstring data = env->NewString(reinterpret_cast<const jchar*>(qdata.constData()), qdata.length());
    jboolean res = env->CallBooleanMethod(m_intentObject, setStringByKeyID, key, data);
    env->DeleteLocalRef(key);
    env->DeleteLocalRef(data);
    s_javaVM->DetachCurrentThread();

    return res;
}

bool TupAndroidIntents::setUrl(const QString &url)
{
    return setStringById(setUrlMethodID,url); 
}

QString TupAndroidIntents::getMediaStorage()
{
    return getStringFromId(getMediaStorageMethodID);
}

/* PRIMITIVAS */

bool TupAndroidIntents::setStringById(jmethodID id,const QString &qstr)
{
    if (!m_intentObject)return false;

    JNIEnv* env;
    if (s_javaVM->AttachCurrentThread(&env, NULL) < 0) {
        qCritical()<<"AttachCurrentThread failed";
        return false;
    }

    jstring str = env->NewString(reinterpret_cast<const jchar*>(qstr.constData()), qstr.length());
    jboolean res = env->CallBooleanMethod(m_intentObject, id, str);
    env->DeleteLocalRef(str);
    s_javaVM->DetachCurrentThread();

    return res;
}

QString TupAndroidIntents::getStringFromId(jmethodID id)
{
    if (!m_intentObject)return 0;

    JNIEnv* env;
    if (s_javaVM->AttachCurrentThread(&env, NULL) < 0) {
        qCritical()<<"AttachCurrentThread failed";
        return 0;
    }

    jobject jsout  = env->CallObjectMethod(m_intentObject,id);
    const char *resultCStr = env->GetStringUTFChars((jstring)jsout, 0);

    QByteArray qbArry(resultCStr);
    QString str(qbArry);
    s_javaVM->DetachCurrentThread();

    return str;
}

// this method is called immediately after the module is load
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* /*reserved*/)
{
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        qCritical()<<"Can't get the enviroument";
        return -1;
    }

    s_javaVM = vm;
    // search for our class
    jclass clazz=env->FindClass("org/kde/necessitas/origo/QAndroidIntent");
    if (!clazz) {
        qCritical()<<"Can't find QSimpleAudioPlayer class";
        return -1;
    }
    // keep a global reference to it
    androidIntentClassID = (jclass)env->NewGlobalRef(clazz);

    // search for its contructor
    constructorMethodID = env->GetMethodID(androidIntentClassID, "<init>", "()V");
    if (!constructorMethodID) {
        qCritical()<<"Can't find QSimpleAudioPlayer class contructor";
        return -1;
    }

    // search for setUrl method
    setUrlMethodID = env->GetMethodID(androidIntentClassID, "setUrl", "(Ljava/lang/String;)Z");
    if (!setUrlMethodID) {
        qCritical()<<"Can't find setUrl method";
        return -1;
    }

    // search for getMediaStorage method
    getMediaStorageMethodID = env->GetMethodID(androidIntentClassID, "getMediaStorage", "()Ljava/lang/String;");
    if (!getMediaStorageMethodID) {
        qCritical()<<"Can't find setUrl method";
        return -1;
    }

    // getLastFrameStringID
    getLastSaveMethodID = env->GetMethodID(androidIntentClassID, "getLastSave", "()Ljava/lang/String;");
    if (!getLastSaveMethodID) {
        qCritical()<<"Can't find setUrl method";
        return -1;
    }

    // getLastFrameStringID
    setLastSaveMethodID = env->GetMethodID(androidIntentClassID, "setLastSave", "(Ljava/lang/String;)Z");
    if (!getLastSaveMethodID) {
        qCritical()<<"Can't find setUrl method";
        return -1;
    }

    // getStringFromKeyID
    getStringFromKeyID = env->GetMethodID(androidIntentClassID, "getStringFromKey", "(Ljava/lang/String;)Ljava/lang/String;");
    if (!getStringFromKeyID) {
        qCritical()<<"Can't find setUrl method";
        return -1;
    }


    // setStringByKeyID
    setStringByKeyID = env->GetMethodID(androidIntentClassID, "setStringByKey", "(Ljava/lang/String;Ljava/lang/String;)Z");
    if (!setStringByKeyID) {
        qCritical()<<"Can't find setUrl method";
        return -1;
    }


    return JNI_VERSION_1_6;
}
