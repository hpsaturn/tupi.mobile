#include "android_intents.h"
#include <QDebug>


static JavaVM* s_javaVM = 0;
static jclass s_androidIntentClassID = 0;
static jmethodID s_androidIntentConstructorMethodID=0;
static jmethodID s_androidIntentSetUrlMethodID=0;

AndroidIntents::AndroidIntents()
{
    JNIEnv* env;
    // Qt is running in a different thread than Java UI, so you always Java VM *MUST* be attached to current thread
    if (s_javaVM->AttachCurrentThread(&env, NULL)<0)
    {
        qCritical()<<"AttachCurrentThread failed";
        return;
    }

    // Create a new instance of QSimpleAudioPlayer
    m_intentObject = env->NewGlobalRef(env->NewObject(s_androidIntentClassID, s_androidIntentConstructorMethodID));
    if (!m_intentObject)
    {
        qCritical()<<"Can't create the player";
        return;
    }

    // Don't forget to detach from current thread
    s_javaVM->DetachCurrentThread();
}

AndroidIntents::~AndroidIntents()
{
    if (!m_intentObject)
        return;

    JNIEnv* env;
    if (s_javaVM->AttachCurrentThread(&env, NULL)<0)
    {
        qCritical()<<"AttachCurrentThread failed";
        return;
    }

    s_javaVM->DetachCurrentThread();
}

bool AndroidIntents::setUrl(const QString &url)
{
    if (!m_intentObject)
        return false;

    JNIEnv* env;
    if (s_javaVM->AttachCurrentThread(&env, NULL)<0)
    {
        qCritical()<<"AttachCurrentThread failed";
        return false;
    }
    jstring str = env->NewString(reinterpret_cast<const jchar*>(url.constData()), url.length());
    jboolean res = env->CallBooleanMethod(m_intentObject, s_androidIntentSetUrlMethodID, str);
    env->DeleteLocalRef(str);
    s_javaVM->DetachCurrentThread();
    return res;
}


// our native method, it is called by the java code above
static int addTwoNumbers(JNIEnv * /*env*/, jobject /*thiz*/,int a, int b)
{
    return a+b;
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
    if (!clazz)
    {
        qCritical()<<"Can't find QSimpleAudioPlayer class";
        return -1;
    }
    // keep a global reference to it
    s_androidIntentClassID = (jclass)env->NewGlobalRef(clazz);

    // search for its contructor
    s_androidIntentConstructorMethodID = env->GetMethodID(s_androidIntentClassID, "<init>", "()V");
    if (!s_androidIntentConstructorMethodID)
    {
        qCritical()<<"Can't find QSimpleAudioPlayer class contructor";
        return -1;
    }

    // search for setUrl method
    s_androidIntentSetUrlMethodID = env->GetMethodID(s_androidIntentClassID, "setUrl", "(Ljava/lang/String;)Z");
    if (!s_androidIntentSetUrlMethodID)
    {
        qCritical()<<"Can't find setUrl method";
        return -1;
    }


    return JNI_VERSION_1_6;
}
