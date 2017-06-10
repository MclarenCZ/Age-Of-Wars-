#include "view.h"
#include <QDebug>
#include <QTimer>
#include <stdio.h>
#include <stdlib.h>
#include <QOpenGLWidget>
#include <QProcess>
#include <QApplication>


View::View()
{

}

View::View(QGraphicsScene *scene)
{
    setScene(scene);//musi byt pred pouzitim this->scene()
    ShowMenu();

}

void View::CreateTimer()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start(30);
}

void View::SpawnPlayer(QString type)
{

    Player * player = new Player(type.toInt());
    this->scene()->addItem(player);
    playerList.append(player);
    player->setPos(150,100);


}

void View::SpawnEnemy(QString type)
{
    Enemy * enemy = new Enemy(type.toInt());
    this->scene()->addItem(enemy);
    enemyList.append(enemy);
    enemy->setPos(850,100);
}

void View::SpawnBase()
{
    Base *myBase = new Base();
    Base *enemyBase = new Base();
    this->scene()->addItem(myBase);
    myBase->setPos(0,100);//upravit
    this->scene()->addItem(enemyBase);
    enemyBase->setPos(1000,100);//upravit
}

void View::MovePlayers()
{

    for (int i = 0; i < playerList.length(); ++i) {
        int speed = playerList[i]->speed;
        QPointF smer(speed,0);
        playerList[i]->setPos(playerList[i]->pos()+smer);
    }
}

void View::MoveEnemyPlayers()
{

    for (int i = 0; i <enemyList.length(); ++i) {
        int speed = enemyList[i]->speed;
        speed = speed * -1;
        QPointF smer(speed,0);
        enemyList[i]->setPos(enemyList[i]->pos()+smer);
    }
}

void View::Update()
{
    MovePlayers();
    MoveEnemyPlayers();
    Collision();
}

void View::ShowMenu()
{
    //potom s zobrazenym menu a tlacitky
    qDebug() << "zobrazení menu - docasne nepouzite";
    StartGame();
}
void View::Collision()
{
    for (int x = 0; x < playerList.length(); ++x) {
        QList<QGraphicsItem *> list = playerList[x]->collidingItems();
        foreach(QGraphicsItem * i, list)
        {
            Enemy * enemy=dynamic_cast<Enemy *>(i);
            if(enemy){
                qDebug() <<"Colide with enemy";
                playerList[x]->speed = 0;
//                qDebug() <<"nice";
            }

        }
   }
    for (int x = 0; x < enemyList.length(); ++x) {
        QList<QGraphicsItem *> list = enemyList[x]->collidingItems();
        foreach(QGraphicsItem * i, list)
        {
            Player * player=dynamic_cast<Player *>(i);
            if(player){
                qDebug() <<"Colide with player";
                enemyList[x]->speed = 0;
//                qDebug() <<"nice";
            }

        }
   }


}

void View::DisplayControls()
{
    qDebug() << "zobrazení ovládacích tlačítek";
}

void View::StartGame()
{
    qDebug() << "starting game";
    status = running;
    CreateTimer();
    SpawnBase();

    SpawnPlayer("001");//xx - level(age)(0 - 99), x - type(1 - 4)
    SpawnEnemy("001");//xx - level(age)(0 - 99), x - type(1 - 4)
}

void View::keyPressEvent(QKeyEvent *event)
{

}

void View::keyReleaseEvent(QKeyEvent *event)
{

}

void View::CreateGame()
{

}
