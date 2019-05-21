#include "sapi.h"
#include "motores.h"

int main(void)
{

  /* Inicializa EduCIAA */
  boardConfig();

  /* Inicializa Motores */
  iniMotores();


  while(1){
	  prenderMotores();

	  //escribirPWMMotores(250, 250);
	  escribirMotores(50, 50);
	  delay(5000);
	  apagarMotores();
	  delay(5000);

	  escribirMotores(0, 0);
	  delay(5000);
	  apagarMotores();
	  delay(5000);

	  escribirMotores(100, 100);
	  delay(5000);
	  apagarMotores();
	  delay(5000);


	  escribirMotores(-50, -50);
	  delay(5000);
	  apagarMotores();
	  delay(5000);

	  escribirMotores(0, 0);
	  delay(5000);
	  apagarMotores();
	  delay(5000);

	  escribirMotores(-100, -100);
	  delay(5000);
	  apagarMotores();
	  delay(5000);

  }
  return 0;
}


