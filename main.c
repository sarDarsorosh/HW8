#include <stdio.h>
#include <stdlib.h>



int main() {
    // ساختار زمان
struct Time {
    int min;
    int sec;
};

// ساختار دونده
struct Runner {
    char firstName[50];
    char lastName[50];
    int ID;
    struct Time *record;
    struct Time runningTime;
};
    int numOfParticipants;

    printf("Enter the number of participants: ");
    scanf("%d", &numOfParticipants);

    // ایجاد آرایه از ساختارهای دونده
    struct Runner participants[numOfParticipants];

    // ورود اطلاعات برای هر شرکت‌کننده
    for (int i = 0; i < numOfParticipants; ++i) {
        printf("\nEnter information for participant %d:\n", i + 1);

        printf("Enter first name: ");
        scanf("%s", participants[i].firstName);

        printf("Enter last name: ");
        scanf("%s", participants[i].lastName);

        printf("Enter ID: ");
        scanf("%d", &participants[i].ID);

        // اختصاص حافظه برای رکورد بهترین زمان به شکل پوینتر
        participants[i].record = (struct Time *)malloc(sizeof(struct Time));

        printf("Enter record (minutes seconds): ");
        scanf("%d %d", &participants[i].record->min, &participants[i].record->sec);

        printf("Enter running time (minutes seconds): ");
        scanf("%d %d", &participants[i].runningTime.min, &participants[i].runningTime.sec);
    }

    // پیدا کردن برنده و چاپ اطلاعات مربوطه
    struct Runner winner = participants[0]; // فرض کردن اولین شرکت‌کننده به عنوان برنده

    for (int i = 1; i < numOfParticipants; ++i) {
        if (participants[i].runningTime.min < winner.runningTime.min ||
            (participants[i].runningTime.min == winner.runningTime.min &&
             participants[i].runningTime.sec < winner.runningTime.sec)) {
            winner = participants[i];
        }
    }

    printf("\nWinner: %s %s\n", winner.firstName, winner.lastName);

    if (winner.runningTime.min < winner.record->min ||
        (winner.runningTime.min == winner.record->min &&
         winner.runningTime.sec < winner.record->sec)) {
        printf("The runner has broken their own record.\n");
    } else {
        printf("The runner couldn't break their own record.\n");
    }

    // پیدا کردن بهترین رکورد کل شرکت‌کنندگان
    struct Time overallBestRecord = participants[0].runningTime;

    for (int i = 1; i < numOfParticipants; ++i) {
        if (participants[i].runningTime.min < overallBestRecord.min ||
            (participants[i].runningTime.min == overallBestRecord.min &&
             participants[i].runningTime.sec < overallBestRecord.sec)) {
            overallBestRecord = participants[i].runningTime;
        }
    }

    if (overallBestRecord.min < winner.record->min ||
        (overallBestRecord.min == winner.record->min &&
         overallBestRecord.sec < winner.record->sec)) {
        printf("The participant set a new overall best record.\n");
    } else {
        printf("The participant couldn't break the overall best record.\n");
    }

    // چاپ اطلاعات دوندگان به ترتیب رکورد
    printf("\nRunners' information sorted by their records (from lowest to highest):\n");
    printf("First Name | Last Name | ID | Record (min:sec) | Running Time (min:sec)\n");

    for (int i = 0; i < numOfParticipants; ++i) {
        printf("%-10s | %-9s | %-2d | %02d:%02d           | %02d:%02d\n", participants[i].firstName,
               participants[i].lastName, participants[i].ID, participants[i].record->min,
               participants[i].record->sec, participants[i].runningTime.min, participants[i].runningTime.sec);

        free(participants[i].record); // آزاد کردن حافظه مخصوص رکورد
    }

    return 0;
}
