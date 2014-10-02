/*

	Описания кроссплатформенных функций, зависящих от ОС

*/

#ifdef __APPLE__

#endif

#ifdef __MINGW32__
//если вдруг случилось так, что винда...
#include <windows.h>

//вроде как возвращает скока там прошло с момента загрузки, правда оно переполняется периодически
long int MilliSecs()
{
	return GetTickCount();
}

//миллисекундная задержка
void Delay( int millis )
{
	Sleep(millis);
	//правда особенность этого вызова такова, что меньше нескольких мс оно не умеет вроде, не помню точно сколько минимум...
}

#endif

#ifdef __linux
//варианты для linux
#include <sys/time.h>

//текущее время в миллисекундах
//данный вызов возвращает несколько иное, чем под виндой, но так как в коде используется дельта - то пофик, главное чтобы стабильно
long int MilliSecs()
{
	//но фишка в том, что gettimeofday возвращает наносекунды, поэтому надо перевести в милисекунды
	int t;
	struct timeval tv;
	gettimeofday(&tv,0);
	t=tv.tv_sec*1000;
	t+=tv.tv_usec/1000;
	return t;
}

//вот это работает тоже иначе, чем под вынью
//usleep тоже в наносекундах
//формально, оно может и на наносекунды задерживаться, но нам таковое не надо
void Delay( int millis )
{
	int i,e;
	if( millis<0 ) return;

	e=MilliSecs()+millis;
	
	for( i=0;;++i ){
		int t=e-MilliSecs();
		if( t<=0 ){
			if( !i ) usleep( 0 );	//always sleep at least once.
			break;
		}
		usleep( t*1000 );
	}
}

#endif
