//#define DEBUG // à commenter pour enlever les traces

#ifdef DEBUG
#define DPRINTF(s)   {Serial.print(F(s));}
#define DPRINTLNF(s)   {Serial.println(F(s));}
#define DPRINT(x)  {Serial.print(x);}
#define DPRINTLN(x)  {Serial.println(x);}
#else
#define DPRINTF(s)
#define DPRINTLNF(s)
#define DPRINT(x)
#define DPRINTLN(x)

#endif
