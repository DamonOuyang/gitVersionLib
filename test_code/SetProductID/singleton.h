#ifndef _SINGLETON_H_
#define _SINGLETON_H_ 

template<class T>
class singleton: public T
{
private:
	singleton(){}
	~singleton(){}

public:
	static T &instance()
	{
		static singleton<T> s_oT;
		return(s_oT);
	}
};

#endif //#ifndef _SINGLETON_H_

