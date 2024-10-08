# Juego-Arduino-OLED-Space

Este proyecto es un juego simple desarrollado para Arduino, que utiliza una pantalla OLED para la visualización. El jugador controla una nave espacial y debe disparar a los enemigos que descienden desde la parte superior de la pantalla.

## Descripción del Proyecto

El juego "Arduino OLED Space" es una recreación del clásico juego de disparos espaciales. El jugador controla una nave en la parte inferior de la pantalla y debe disparar a los enemigos que aparecen en la parte superior. A medida que el juego avanza, la dificultad aumenta y el jugador gana puntos por cada enemigo destruido.

### Características principales:

- Control de la nave mediante un potenciómetro
- Disparo de proyectiles con un botón
- Enemigos que descienden desde la parte superior de la pantalla
- Sistema de puntuación y niveles
- Efectos visuales simples para explosiones

## Materiales Necesarios

Para construir este proyecto, necesitarás los siguientes componentes:

1. Arduino Nano
2. Pantalla OLED (128x64 píxeles)
3. Potenciómetro
4. Botón pulsador
5. Cables de conexión
6. Protoboard (para el montaje experimental)

## Contenido del Repositorio

Este repositorio contiene:

1. Código fuente del juego (`juego_con_pantalla_oled.ino`)
2. Diagrama de conexiones para montaje en protoboard (`Tablero experimental.png`)
3. Diagrama del circuito para montaje final (`Schematic_Juego_Nave_Arduino_oled_2024-10-07.png`)
4. Diagrama del circuito para montaje final (`Schematic_Juego_Nave_Arduino_oled_2024-10-07.pdf`)
5. Este archivo README.md

## Sobre el Código

El código está escrito en C++ para Arduino y utiliza las siguientes bibliotecas:

- SPI
- Wire
- Adafruit_GFX
- Adafruit_SSD1306

El juego está estructurado en varias funciones principales que manejan la lógica del juego, la actualización de la pantalla y la detección de colisiones. Los comentarios en el código proporcionan una explicación detallada de cada sección.

## Montaje

Puedes montar este proyecto de dos maneras:

1. **Tablero Experimental**: Sigue el diagrama de conexiones para protoboard (`Tablero experimental.png`) para un montaje rápido y fácil de modificar.

2. **Montaje Final**: Para una versión más compacta y permanente, sigue el diagrama del circuito (`Schematic_Juego_Nave_Arduino_oled_2024-10-07.png`).

## Cómo Jugar

1. Mueve el potenciómetro para controlar la posición horizontal de tu nave.
2. Presiona el botón para disparar a los enemigos.
3. Evita que los enemigos lleguen a la parte inferior de la pantalla.
4. Gana puntos por cada enemigo destruido.
5. El juego se vuelve más difícil a medida que avanzas de nivel.

## Contribuciones

¡Las contribuciones son bienvenidas! Si tienes ideas para mejorar el juego o el código, no dudes en hacer un fork del repositorio y enviar tus pull requests.

## Licencia

Este proyecto está bajo la licencia MIT. Consulta el archivo `LICENSE` para más detalles.

---

Esperamos que disfrutes construyendo y jugando este juego espacial con Arduino. Si tienes alguna pregunta o sugerencia, no dudes en abrir un issue en este repositorio.

¡Diviértete explorando el espacio con tu Arduino!
