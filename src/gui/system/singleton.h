#ifndef SINGLETON_H
#define SINGLETON_H

#define FONT(fontName)  Singleton<fontName>::instance()

template<typename T>
class Singleton final
{
    public:
        static const T &instance();

    private:
        Singleton(const Singleton &) = delete;
        Singleton &operator=(const Singleton &) = delete;
};

template<typename T>
const T &Singleton<T>::instance()
{
    static const T inst ;
    return inst;
}

#endif // SINGLETON_H
