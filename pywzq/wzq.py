#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
author: GeekSword
website: onestraw.net
"""
import sys
from PyQt4 import QtGui, QtCore

'''弹出对话框类'''
class Game_Over_Dialog(QtGui.QDialog):
    def __init__(self, text, parent=None):
        QtGui.QDialog.__init__(self,parent)
        self.setFixedSize(200,120)
        self.setWindowTitle("Game Over")
        self.label=QtGui.QLabel(text)
        self.quit=QtGui.QPushButton("Quit",self)
        self.quit.setGeometry(62,40,75,30)
        layout = QtGui.QGridLayout()
        layout.addWidget(self.quit,1,0)
        layout.addWidget(self.label,0,0)
        self.setLayout(layout)
        self.connect(self.quit,QtCore.SIGNAL("clicked()"),self,QtCore.SLOT("close()"))
      
''' wuziqi MAIN WINDOW class '''
class WZQ_MAIN_WIN(QtGui.QWidget):
    def __init__(self):
        super(WZQ_MAIN_WIN, self).__init__()
        self.painter = QtGui.QPainter()
        self.lineNum=15
        self.grid_space=35
        self.margin = 20
        self.width=(self.lineNum-1)*self.grid_space + self.margin*2
        self.height=(self.lineNum-1)*self.grid_space + self.margin*2
        self.initUI()

        self.computer = 1
        self.man = 2
        self.gameOverFlag=0
        #initial the chess matrix
        self.chessBoard=list()
        for i in range(self.lineNum):
            rowlist = list()
            for j in range(self.lineNum):
                rowlist.append(0)
            self.chessBoard.append(rowlist)
 		
    def initUI(self):
        self.setGeometry(300, 300, self.width,self.height)
        self.setWindowTitle(r'One Straw Gobang')
        self.move(0, 0)
        #set background color 
        self.autoFillBackground()
        palette = self.palette()
        color = QtGui.QColor(255, 80, 0, 160)
        palette.setColor(QtGui.QPalette.Window,color)
        self.setPalette(palette)

        self.show()
    #画出15x15棋盘
    def drawChessBoard(self):
        pen = QtGui.QPen(QtCore.Qt.black, 2, QtCore.Qt.SolidLine)
        self.painter.setPen(pen)
        #draw horizontal line
        startx = self.margin
        endx = self.width - self.margin
        for k in range(self.lineNum):
            starty = self.margin + k*self.grid_space
            endy = starty
            self.painter.drawLine(startx, starty, endx, endy)
        #draw vertical line
        starty = self.margin
        endy = self.width - self.margin
        for k in range(self.lineNum):
            startx = self.margin + k*self.grid_space
            endx = startx
            self.painter.drawLine(startx, starty, endx, endy)
    #显示一个棋子    
    def drawChessMan(self, x, y, who):
        if who == self.computer:
            self.painter.setBrush(QtGui.QColor(0, 0, 0, 200))
        elif who == self.man:
            self.painter.setBrush(QtGui.QColor(255,255,255, 200))
        dx = y*self.grid_space + self.margin - self.grid_space/2
        dy = x*self.grid_space + self.margin - self.grid_space/2
        self.painter.drawEllipse(dx, dy, self.grid_space, self.grid_space)
        
    def paintEvent(self, event):
        print "this is an event"
        self.painter.begin(self)
        self.drawChessBoard()
        for i in range(self.lineNum):
            for j in range(self.lineNum):
                if self.chessBoard[i][j]!=0:
                    self.drawChessMan(i, j, self.chessBoard[i][j])
        self.painter.end()
			
    def x(self, pos):
        return (pos.x()-self.margin + self.grid_space/2)/self.grid_space
    def y(self, pos):
        return (pos.y()-self.margin + self.grid_space/2)/self.grid_space

    def mousePressEvent(self, event):
        clickPos = event.pos()
        x=self.y(clickPos)
        y=self.x(clickPos)
        #print "coord position(%d,%d)" %(x,y)
        if not self.gameOverFlag and event.button()==QtCore.Qt.LeftButton and not self.chessBoard[x][y]:
            print "left click"
            #玩家下
            self.chessBoard[x][y] = self.man
            self.repaint()
            #判断玩家有没有赢
            if self.isWin(x,y,self.man)==1:
                print "Man Win"
                self.gameOverFlag = 1
                self.showGameOver(self.man)
            else:
                #print "continue"
                #电脑下
                coord = self.forecast()#self.computerStep()
                self.chessBoard[coord[0]][coord[1]]=self.computer
                self.repaint()
                #判断电脑有没有赢
                if self.isWin(coord[0],coord[1],self.computer)==1:
                    print "Computer Win"
                    self.gameOverFlag = 1
                    self.showGameOver(self.computer)
            
    #弹出输赢对话框        
    def showGameOver(self,who):
        if who==self.computer:
            text="Computer Win!"
        else:
            text="Player Win!"
        dlg=Game_Over_Dialog(text)
        dlg.show()
        dlg.exec_()  
    #电脑落子
    def computerStep(self):
        #1.电脑防守,假设玩家下这个位置，能获得很大优势，电脑就要抢占这个位置
        maxD=0
        stepPosD=[0,0]
        for i in range(self.lineNum):
            for j in range(self.lineNum):
                if self.chessBoard[i][j]:
                    continue
                self.chessBoard[i][j]==self.man
                temp=self.evalBoard(i,j,self.man)
                if maxD < temp:
                    maxD=temp
                    stepPosD=[i,j]
                    print "(%d,%d)=%d" %(i,j,temp)
                self.chessBoard[i][j]==0
        #2.电脑进攻，电脑去试探每个步骤，看看优势
        maxA=0
        stepPosA=[0,0]
        for i in range(self.lineNum):
            for j in range(self.lineNum):
                if self.chessBoard[i][j]:
                    continue
                self.chessBoard[i][j]==self.computer
                temp=self.evalBoard(i,j,self.computer)
                if maxA < temp:
                    maxA=temp
                    stepPosA=[i,j]
                    print "(%d,%d)=%d" %(i,j,temp)
                self.chessBoard[i][j]==0
        #3.判断电脑是进攻还是防守
        if maxA > maxD:
            return stepPosA
        else:
            return stepPosD
    #玩家落子
    def playerStep(self):
        #1.玩家防守,假设电脑下这个位置，能获得很大优势，玩家就要抢占这个位置
        maxD=0
        stepPosD=[0,0]
        for i in range(self.lineNum):
            for j in range(self.lineNum):
                if self.chessBoard[i][j]:
                    continue
                self.chessBoard[i][j]==self.computer
                temp=self.evalBoard(i,j,self.computer)
                if maxD < temp:
                    maxD=temp
                    stepPosD=[i,j]
                    print "(%d,%d)=%d" %(i,j,temp)
                self.chessBoard[i][j]==0
        #2.玩家，玩家去试探每个步骤，看看优势
        maxA=0
        stepPosA=[0,0]
        for i in range(self.lineNum):
            for j in range(self.lineNum):
                if self.chessBoard[i][j]:
                    continue
                self.chessBoard[i][j]==self.man
                temp=self.evalBoard(i,j,self.man)
                if maxA < temp:
                    maxA=temp
                    stepPosA=[i,j]
                    print "(%d,%d)=%d" %(i,j,temp)
                self.chessBoard[i][j]==0
        #3.判断玩家是进攻还是防守
        if maxA > maxD:
            return stepPosA
        else:
            return stepPosD

    def forecast(self):
        nextPos=[-1,-1]
        minV=100000
        for i in range(self.lineNum):
            for j in range(self.lineNum):
                if self.chessBoard[i][j]:
                    continue
                self.chessBoard[i][j] = self.computer
                step1 = self.playerStep()
                self.chessBoard[step1[0]][step1[1]] = self.man
                #step2 = self.computerStep()
                #self.chessBoard[step2[0]][step2[1]] = self.computer
                temp = self.evalBoard(step1[0],step1[1],self.man)
                if minV > temp:
                    minV=temp
                    nextPos=[i,j]
                self.chessBoard[i][j] = 0
                self.chessBoard[step1[0]][step1[1]] = 0
                #self.chessBoard[step2[0]][step2[1]] = 0
        return nextPos            
    #根据连线的形式进行打分
    def score(self, startFlag, endFlag, num):
        ret = 0
        if startFlag and endFlag:
            if num == 1:
                ret=10
            elif num==2:
                ret = 100
            elif num==3:
                ret = 1000
            elif num==4:
                ret =50000
        elif startFlag or endFlag:
            if num ==2:
                ret=50
            elif num==3:
                ret=500
            elif num==4:
                ret=10000
        if num==5:
            ret =100000
        return ret
    
    ##估值函数，在[x][y]位置放上who之后，在who一方进行评估    
    def evalBoard(self, x, y, who):
        value = 0
        #------左右方向------
        count = 1
        #向左
        startFlag=0
        endFlag=0
        for k in range(y-1,-1,-1):
            if self.chessBoard[x][k]==who:
                count += 1
            else:
                if self.chessBoard[x][k]==0:
                    startFlag=1
                break
        #向右
        for k in range(y+1,self.lineNum,1):
            if self.chessBoard[x][k]==who:
                count += 1
            else:
                if self.chessBoard[x][k]==0:
                    endFlag=1
                break
        
        value += self.score(startFlag, endFlag, count)  
        #-----上下方向------
        count = 1
        #向上
        startFlag=0
        endFlag=0
        for k in range(x-1,-1,-1):
            if self.chessBoard[k][y]==who:
                count += 1
            else:
                if self.chessBoard[k][y]==0:
                    startFlag=1
                break
        #向下
        for k in range(x+1, self.lineNum,1):
            if self.chessBoard[k][y]==who:
                count += 1
            else:
                if self.chessBoard[k][y]==0:
                    endFlag=1
                break
        value += self.score(startFlag, endFlag, count)
        
        #-----左上  右下方向------
        count = 1
        i = x
        j = self.lineNum - y -1
        if x > y:
            i = y
            j = self.lineNum - x -1
        #向左上
        startFlag=0
        endFlag=0
        for k in range(1,i+1,1):
            if self.chessBoard[x-k][y-k]==who:
                count += 1
            else:
                if self.chessBoard[x-k][y-k]==0:
                    startFlag=1
                break
        #向右下
        for k in range(1, j+1, 1):
            if self.chessBoard[x+k][y+k]==who:
                count += 1
            else:
                if self.chessBoard[x+k][y+k]==0:
                    endFlag=1
                break
        value += self.score(startFlag, endFlag, count)
        
        #-----左下  右上方向------
        count = 1
        if y > self.lineNum - x -1:
            i = self.lineNum - x -1
        else:
            i = y
        if x > self.lineNum - y -1:
            j = self.lineNum - y -1
        else:
            j = x
        #向左下
        startFlag=0
        endFlag=0
        for k in range(1,i+1,1):
            if self.chessBoard[x+k][y-k]==who:
                count += 1
            else:
                if self.chessBoard[x+k][y-k]==0:
                    startFlag=1
                break
        #向右上
        for k in range(1,j+1,1):
            if self.chessBoard[x-k][y+k]==who:
                count += 1
            else:
                if self.chessBoard[x-k][y+k]==0:
                    endFlag=1
                break
        value += self.score(startFlag, endFlag, count)
        
        return value

    ##当who在(x,y)位置落子后，判断它是否赢了
    def isWin(self, x, y, who):
        #------左右方向------
        count = 1
        #向左
        for k in range(y-1,-1,-1):
            if self.chessBoard[x][k]==who:
                count += 1
            else:
                break
        #向右
        for k in range(y+1,self.lineNum,1):
            if self.chessBoard[x][k]==who:
                count += 1
            else:
                break
        if count>4:
            return 1
        #-----上下方向------
        count = 1
        #向上
        for k in range(x-1,-1,-1):
            if self.chessBoard[k][y]==who:
                count += 1
            else:
                break
        #向下
        for k in range(x+1, self.lineNum,1):
            if self.chessBoard[k][y]==who:
                count += 1
            else:
                break
        if count>4:
            return 1
        #-----左上  右下方向------
        count = 1
        i = x
        j = self.lineNum - y -1
        if x > y:
            i = y
            j = self.lineNum - x -1
        #向左上
        for k in range(1,i+1,1):
            if self.chessBoard[x-k][y-k]==who:
                count += 1
            else:
                break
        #向右下
        for k in range(1, j+1, 1):
            if self.chessBoard[x+k][y+k]==who:
                count += 1
            else:
                break
        if count>4:
            return 1
        #-----左下  右上方向------
        count = 1
        if y > self.lineNum - x -1:
            i = self.lineNum - x -1
        else:
            i = y
        if x > self.lineNum - y -1:
            j = self.lineNum - y -1
        else:
            j = x
        #向左下
        for k in range(1,i+1,1):
            if self.chessBoard[x+k][y-k]==who:
                count += 1
            else:
                break
        #向右上
        for k in range(1,j+1,1):
            if self.chessBoard[x-k][y+k]==who:
                count += 1
            else:
                break
        if count>4:
            return 1
        return 0

def main():
    app = QtGui.QApplication(sys.argv)
    ex = WZQ_MAIN_WIN()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
