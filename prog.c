
#include <stdio.h>
#include <string.h>
#define SIZE 20 

// تعريف هيكلية المخزن الدائري كما ورد في الـ Pseudocode
struct CircularBuffer {
    char buffer[SIZE];
    int head;
    int tail;
    int count;
};

// دالة التهيئة (Initialization)
void init(struct CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// دالة التحقق من الامتلاء
int isFull(struct CircularBuffer *cb) {
    return cb->count == SIZE;
}

// دالة التحقق من الفراغ
int isEmpty(struct CircularBuffer *cb) {
    return cb->count == 0;
}

// دالة الكتابة (Write) مع معالجة الـ Overflow
void write_to_buffer(struct CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("\n[Error] Buffer Overflow! Cannot add: %c", data);
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE; // الالتفاف الدائري
    cb->count++;
}

// دالة القراءة (Read) مع معالجة الـ Underflow
char read_from_buffer(struct CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("\n[Error] Buffer Underflow!");
        return '\0';
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE; // الالتفاف الدائري
    cb->count--;
    return data;
}

int main() {
    struct CircularBuffer cb;
    init(&cb); // تنفيذ دالة التهيئة [cite: 78]

    char name[100];
    
    // إدخال الاسم [cite: 80]
    printf("Enter your name: ");
    scanf("%s", name); 

    // إضافة اللاحقة المطلوبة [cite: 83]
    strcat(name, "-CE-ESY");
    
    printf("\n--- Processing Data ---\n");
    
    // خزن الناتج داخل المخزن [cite: 85, 86]
    for (int i = 0; i < strlen(name); i++) {
        write_to_buffer(&cb, name[i]);
    }

    // عرض النتيجة والتأكد أن المخزن سيصبح فارغاً [cite: 88, 91]
    printf("Buffer Output: ");
    while (!isEmpty(&cb)) {
        char c = read_from_buffer(&cb);
        if (c != '\0') printf("%c", c);
    }
    
    // التحقق النهائي من حالة المخزن [cite: 21]
    if (isEmpty(&cb)) {
        printf("\n\nStatus: Buffer is now empty. Success!");
    }

    return 0;
}
