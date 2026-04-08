#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

long long get_time_ms(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int main(void)
{
    long long start_time;
    long long current_time;
    long long time_passed;
    
    int time_to_burnout = 300; // المبرمج سيحترق إذا لم يعمل لمدة 300 ميلي ثانية

    // 1. نسجل وقت البداية
    start_time = get_time_ms();
    printf("المحاكاة بدأت عند: %lld\n", start_time);

    // 2. محاكاة عمل (مثلاً المبرمج ينتظر الأجهزة أو يقوم بالترجمة)
    // دالة usleep تأخذ الوقت بالميكروثانية، لذا نضرب في 1000
    printf("المبرمج يعمل الآن...\n");
    usleep(2000000 * 1000); // نجعله ينام لمدة 200 ميلي ثانية

    // 3. نسجل الوقت بعد الانتهاء
    current_time = get_time_ms();
    
    // 4. نحسب كم من الوقت مر (الوقت الحالي - وقت البداية)
    time_passed = current_time - start_time;
    printf("الوقت المستغرق: %lld ميلي ثانية\n", time_passed);

    // 5. التحقق من الاحتراق (وهذا ما سيفعله الـ Monitor Thread في مشروعك)
    if (time_passed > time_to_burnout)
    {
        printf("النتيجة: المبرمج احترق! (تجاوز %d ميلي ثانية)\n", time_to_burnout);
    }
    else
    {
        printf("النتيجة: المبرمج بأمان! (العبء أقل من %d ميلي ثانية)\n", time_to_burnout);
    }

    return (0);
}