#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void increaseTemp();
    void decreaseTemp();
    void increaseFlow();
    void decreaseFlow();

    void increaseDuty();
    void decreaseDuty();

protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
