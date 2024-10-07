// Incluimos las bibliotecas necesarias para el proyecto
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definimos las características de la pantalla OLED
#define SCREEN_WIDTH 128 // Ancho de la pantalla en píxeles
#define SCREEN_HEIGHT 64 // Alto de la pantalla en píxeles
#define OLED_RESET     -1 // Pin de reinicio (no se usa)
#define SCREEN_ADDRESS 0x3C // Dirección I2C de la pantalla
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Definimos los pines para el potenciómetro y el botón
#define POTENTIOMETER_PIN A0
#define BUTTON_PIN 2

// Establecemos las dimensiones de los elementos del juego
const int PLAYER_WIDTH = 8;
const int PLAYER_HEIGHT = 8;
const int ENEMY_WIDTH = 8;
const int ENEMY_HEIGHT = 8;
const int BULLET_WIDTH = 2;
const int BULLET_HEIGHT = 4;
const int MAX_PARTICLES = 15;

// Variables para la posición del jugador y estadísticas del juego
int playerX = SCREEN_WIDTH / 2;
int playerY = SCREEN_HEIGHT - PLAYER_HEIGHT - 2;
int score = 0;
int level = 1;

// Estructuras para representar enemigos, balas y partículas
struct Enemy {
  int x;
  int y;
  bool active;
};

struct Bullet {
  int x;
  int y;
  bool active;
};

struct Particle {
  float x;
  float y;
  float vx;
  float vy;
  int life;
};

// Arrays para almacenar múltiples instancias de enemigos, balas y partículas
Enemy enemies[3];
Bullet bullet;
Particle particles[MAX_PARTICLES];

// Función de configuración inicial
void setup() {
  Serial.begin(9600);
  
  // Inicializamos la pantalla OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Falló la asignación de SSD1306"));
    for(;;); // Bucle infinito si falla la inicialización
  }
  
  display.display();
  delay(2000);
  display.clearDisplay();
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Inicializamos los enemigos como inactivos
  for (int i = 0; i < 3; i++) {
    enemies[i].active = false;
  }
  bullet.active = false;
  
  randomSeed(analogRead(A1)); // Inicializamos el generador de números aleatorios
}

// Función principal que se ejecuta continuamente
void loop() {
  // Leemos el valor del potenciómetro para mover al jugador
  int potValue = analogRead(POTENTIOMETER_PIN);
  playerX = map(potValue, 0, 1023, 0, SCREEN_WIDTH - PLAYER_WIDTH);
  
  // Disparamos una bala si se presiona el botón
  if (digitalRead(BUTTON_PIN) == LOW && !bullet.active) {
    bullet.x = playerX + PLAYER_WIDTH / 2 - BULLET_WIDTH / 2;
    bullet.y = playerY;
    bullet.active = true;
  }
  
  // Actualizamos la posición de los elementos del juego
  updateEnemies();
  updateBullet();
  updateParticles();
  checkCollisions();
  
  // Dibujamos todos los elementos en la pantalla
  display.clearDisplay();
  drawPlayer();
  drawEnemies();
  drawBullet();
  drawParticles();
  drawScore();
  display.display();
  
  delay(50); // Pequeña pausa para controlar la velocidad del juego
}

// Función para actualizar la posición de los enemigos
void updateEnemies() {
  for (int i = 0; i < 3; i++) {
    if (!enemies[i].active) {
      // Probabilidad de que aparezca un nuevo enemigo
      if (random(100) < 5 + level) {
        enemies[i].x = random(SCREEN_WIDTH - ENEMY_WIDTH);
        enemies[i].y = 0;
        enemies[i].active = true;
      }
    } else {
      // Movemos el enemigo hacia abajo
      enemies[i].y += 1 + level / 5;
      if (enemies[i].y > SCREEN_HEIGHT) {
        enemies[i].active = false;
        score -= 5;
        if (score < 0) score = 0;
      }
    }
  }
}

// Función para actualizar la posición de la bala
void updateBullet() {
  if (bullet.active) {
    bullet.y -= 4; // La bala se mueve hacia arriba
    if (bullet.y < 0) {
      bullet.active = false;
    }
  }
}

// Función para actualizar las partículas (efecto de explosión)
void updateParticles() {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (particles[i].life > 0) {
      particles[i].x += particles[i].vx;
      particles[i].y += particles[i].vy;
      particles[i].life--;
    }
  }
}

// Función para detectar colisiones entre elementos del juego
void checkCollisions() {
  for (int i = 0; i < 3; i++) {
    if (enemies[i].active) {
      // Colisión jugador-enemigo
      if (playerX < enemies[i].x + ENEMY_WIDTH &&
          playerX + PLAYER_WIDTH > enemies[i].x &&
          playerY < enemies[i].y + ENEMY_HEIGHT &&
          playerY + PLAYER_HEIGHT > enemies[i].y) {
        gameOver();
      }
      
      // Colisión bala-enemigo
      if (bullet.active &&
          bullet.x < enemies[i].x + ENEMY_WIDTH &&
          bullet.x + BULLET_WIDTH > enemies[i].x &&
          bullet.y < enemies[i].y + ENEMY_HEIGHT &&
          bullet.y + BULLET_HEIGHT > enemies[i].y) {
        createExplosion(enemies[i].x, enemies[i].y);
        enemies[i].active = false;
        bullet.active = false;
        score += 10;
        if (score % 50 == 0) {
          level++;
        }
      }
    }
  }
}

// Función para crear el efecto de explosión cuando se destruye un enemigo
void createExplosion(int x, int y) {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    particles[i].x = x + ENEMY_WIDTH / 2;
    particles[i].y = y + ENEMY_HEIGHT / 2;
    particles[i].vx = random(-20, 20) / 10.0;
    particles[i].vy = random(-20, 20) / 10.0;
    particles[i].life = random(10, 20);
  }
}

// Funciones para dibujar los elementos del juego en la pantalla

void drawPlayer() {
  display.drawTriangle(
    playerX, playerY + PLAYER_HEIGHT,
    playerX + PLAYER_WIDTH / 2, playerY,
    playerX + PLAYER_WIDTH, playerY + PLAYER_HEIGHT,
    WHITE
  );
}

void drawEnemies() {
  for (int i = 0; i < 3; i++) {
    if (enemies[i].active) {
      display.drawRect(enemies[i].x, enemies[i].y, ENEMY_WIDTH, ENEMY_HEIGHT, WHITE);
    }
  }
}

void drawBullet() {
  if (bullet.active) {
    display.fillRect(bullet.x, bullet.y, BULLET_WIDTH, BULLET_HEIGHT, WHITE);
  }
}

void drawParticles() {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (particles[i].life > 0) {
      display.drawPixel(particles[i].x, particles[i].y, WHITE);
    }
  }
}

void drawScore() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(score);
  display.setCursor(64, 0);
  display.print("Lvl: ");
  display.print(level);
}

// Función que se ejecuta cuando el jugador pierde
void gameOver() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.print("Game Over!");
  display.setTextSize(1);
  display.setCursor(10, 30);
  display.print("Score: ");
  display.print(score);
  display.setCursor(10, 40);
  display.print("Level: ");
  display.print(level);
  display.display();
  delay(3000);
  score = 0;
  level = 1;
  for (int i = 0; i < 3; i++) {
    enemies[i].active = false;
  }
  bullet.active = false;
}

git init
git add .
git commit -m "Commit inicial: Juego-Arduino-OLED-Space"

git remote add origin https://github.com/GC-Lab-Gonzalo/Juego-Arduino-OLED-Space.git
git branch -M main
git push -u origin main