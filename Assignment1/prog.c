
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 15 

// هيكلية المخزن بأسماء بسيطة
struct MyBuffer {
    char data_arr[MAX_SIZE];
    int read_pos;  // head
    int write_pos; // tail
    int active_elements; // count
};

// دالة التجهيز
void setupBuffer(struct MyBuffer *obj) {
    obj->read_pos = 0;
    obj->write_pos = 0;
    obj->active_elements = 0;
}

// دالة الإضافة مع التحقق من الامتلاء
void pushData(struct MyBuffer *obj, char val) {
    if (obj->active_elements == MAX_SIZE) {
        printf("(!) Full: can't add '%c'\n", val);
        return;
    }
    obj->data_arr[obj->write_pos] = val;
    obj->write_pos = (obj->write_pos + 1) % MAX_SIZE; // حركة الالتفاف
    obj->active_elements++;
}

// دالة السحب مع التحقق من الفراغ
char popData(struct MyBuffer *obj) {
    if (obj->active_elements == 0) {
        return '\0'; 
    }
    char res = obj->data_arr[obj->read_pos];
    obj->read_pos = (obj->read_pos + 1) % MAX_SIZE; // حركة الالتفاف
    obj->active_elements--;
    return res;
}

int main() {
    struct MyBuffer myQ;
    setupBuffer(&myQ);

    char studentName[50];
    
    // طلب الاسم من المستخدم
    printf("Enter Name: ");
    scanf("%s", studentName); 

    // إضافة اللاحقة المطلوبة
    strcat(studentName, "-CE-ESY");
    
    printf("\n--- Start Writing ---\n");
    for (int i = 0; i < strlen(studentName); i++) {
        pushData(&myQ, studentName[i]);
    }

    printf("\n--- Start Reading ---\n");
    printf("Output: ");
    while (myQ.active_elements > 0) {
        char c = popData(&myQ);
        if (c != '\0') printf("%c", c);
    }
    
    printf("\n\nFinal Check: Buffer has %d elements.\n", myQ.active_elements);

    return 0;
} 
