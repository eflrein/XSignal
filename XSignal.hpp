#ifndef _XSIGNAL_HPP_
#define _XSIGNAL_HPP_

#include <list>
#include <functional>
#include <type_traits>
#include <utility>

template<class SignalType>
class Connection{
public:
    using iter_type = typename SignalType::iter_type;
    using return_type = typename SignalType::return_type;

    explicit Connection(SignalType &signal,iter_type itr)
        :m_signal(signal),m_itr(itr){}
    Connection(const Connection &) = delete;
    Connection(Connection &&) = default;
    ~Connection() = default;
    
    Connection &operator=(const Connection &) = delete;
    Connection &operator=(Connection &&) = default;
    
    void disconnect(){
        m_signal._remove(m_itr);
    }
    
    
protected:
private:
    SignalType &m_signal;
    iter_type m_itr;
};

template<class Type>
class Signal{};

///ReturnType must have a default constructor!!!

template<class ReturnType,class...ArgsType>
class Signal<ReturnType(ArgsType...)>{
public:
    using iter_type = typename std::list<std::function<ReturnType(ArgsType...)>>::iterator;
    using return_type = ReturnType;
    
    struct Slot{
        template <class Function>
        Slot(Function &&f)
            :func(std::forward<Function>(f)){}
        std::function<ReturnType(ArgsType...)> func;
        ReturnType ret_value;
    };

    Signal();
    ~Signal();
    
    void _remove(iter_type itr){
        m_slots.erase(itr);
    }
    
    template<class Function>
    auto connect(Function &&func)
        -> Connection<Signal<ReturnType(ArgsType...)>>{
        m_slots.emplace_front(std::forward<Function>(func));
        return Connection<Signal<ReturnType(ArgsType...)>>(*this,m_slots.begin())
    }
        
    auto emit(ArgsType...&&args)
        -> ReturnType{
        
    }
protected:
private:
    std::list<Slot> m_slots;
};

#endif
