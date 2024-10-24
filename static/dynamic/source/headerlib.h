struct complexNumber
{
    int realPart;
    int phantomPart;
};

void readcompl(struct complexNumber* num);
void outcompl(struct complexNumber* num);
struct complexNumber addcompl(struct complexNumber first, struct complexNumber second);
struct complexNumber difcompl(struct complexNumber first, struct complexNumber second);
struct complexNumber mulcompl(struct complexNumber first, struct complexNumber second); //работает неправильно
struct complexNumber divcompl(struct complexNumber first, struct complexNumber second); //работает неправильно
