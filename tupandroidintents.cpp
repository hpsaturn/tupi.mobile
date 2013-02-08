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
static jclass s_androidIntentClassID = 0;
static jmethodID s_androidIntentConstructorMethodID=0;
static jmethodID s_androidIntentSetUrlMethodID=0;
static jmethodID s_androidIntentGetMediaStorageMethodID=0;

TupAndroidIntents::TupAndroidIntents()
{
    JNIEnv* env;
    // Qt is running in a different thread than Java UI, so you always Java VM *MUST* be attached to current thread
    if (s_javaVM->AttachCurrentThread(&env, NULL)<0) {
        qCritical()<<"AttachCurrentThread failed";
        return;
    }

    // Create a new instance of QSimpleAudioPlayer
    m_intentObject = env->NewGlobalRef(env->NewObject(s_androidIntentClassID, s_androidIntentConstructorMethodID));
    if (!m_intentObject) {
        qCritical()<<"Can't create the player";
        return;
    }

    // Don't forget to detach from current thread
    s_javaVM->DetachCurrentThread();
}

TupAndroidIntents::~TupAndroidIntents()
{
    if (!m_intentObject)
        return;

    JNIEnv* env;
    if (s_javaVM->AttachCurrentThread(&env, NULL) < 0) {
        qCritical()<<"AttachCurrentThread failed";
        return;
    }

    s_javaVM->DetachCurrentThread();
}

bool TupAndroidIntents::setUrl(const QString &url)
{
    if (!m_intentObject)
        return false;

    JNIEnv* env;
    if (s_javaVM->AttachCurrentThread(&env, NULL) < 0) {
        qCritical()<<"AttachCurrentThread failed";
        return false;
    }

    jstring str = env->NewString(reinterpret_cast<const jchar*>(url.constData()), url.length());
    jboolean res = env->CallBooleanMethod(m_intentObject, s_androidIntentSetUrlMethodID, str);
    env->DeleteLocalRef(str);
    s_javaVM->DetachCurrentThread();

    return res;
}

QString TupAndroidIntents::getMediaStorage()
{
    if (!m_intentObject)
        return 0;

    JNIEnv* env;
    if (s_javaVM->AttachCurrentThread(&env, NULL) < 0) {
        qCritical()<<"AttachCurrentThread failed";
        return 0;
    }

    jobject jsout  = env->CallObjectMethod(m_intentObject, s_androidIntentGetMediaStorageMethodID);
    const char *resultCStr = env->GetStringUTFChars((jstring)jsout, 0);

    QByteArray qbArry(resultCStr);
    QString str(qbArry);

    /* TODO: REVISAR SI TOCA HACER RELEASE DE LOS STRINGS! */
    s_javaVM->DetachCurrentThread();

    return str;
}

// our native method, it is called by the java code above
static int addTwoNumbers(JNIEnv * /*env*/, jobject /*thiz*/,int a, int b)
{
    return a + b;
}

static JNINativeMethod methods[] = {
    {"addTwoNumbers", "(II)I", (void *)addTwoNumbers}
};

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
    s_androidIntentClassID = (jclass)env->NewGlobalRef(clazz);

    // search for its contructor
    s_androidIntentConstructorMethodID = env->GetMethodID(s_androidIntentClassID, "<init>", "()V");
    if (!s_androidIntentConstructorMethodID) {
        qCritical()<<"Can't find QSimpleAudioPlayer class contructor";
        return -1;
    }

    // search for setUrl method
    s_androidIntentSetUrlMethodID = env->GetMethodID(s_androidIntentClassID, "setUrl", "(Ljava/lang/String;)Z");
    if (!s_androidIntentSetUrlMethodID) {
        qCritical()<<"Can't find setUrl method";
        return -1;
    }

    // search for getMediaStorage method
    s_androidIntentGetMediaStorageMethodID = env->GetMethodID(s_androidIntentClassID, "getMediaStorage", "()Ljava/lang/String;");

    if (!s_androidIntentSetUrlMethodID) {
        qCritical()<<"Can't find setUrl method";
        return -1;
    }
    return JNI_VERSION_1_6;
}
