#ifndef CALLBACK_H
#define CALLBACK_H

class Callback
{
public:
    virtual void call() = 0;
};

class StaticCallback : public Callback
{
private:
    void (*v)();

public:
    StaticCallback(void (*vv)()) : v(vv)
    {
    }

    virtual void Call()
    {
        v();
    }
};

#endif