/*                 _ooOoo_ 
                  o8888888o 
                  88" . "88 
                  (| -_- |) 
                   O\ = /O 
               ____/`---*\____ 
                .  \\| |// `. 
              / \\||| : |||// \ 
            / _||||| -:- |||||- \ 
              | | \\\ - /// | | 
            | \_| .\\---//. | | 
            \  .-\__ `-` ___/-. / 
          ___`. .* /--.--\ `. . __ 
       ."" *< `.___\_<|>_/___.* >*"". 
      | | : `- \`.;`\ _ /`;.`/ - ` : | | 
        \ \ `-. \_ __\ /__ _/ .-` / / 
======`-.____`-.___\_____/___.-`____.-====== 
............................................. 
*/               

#include<QtWidgets>
#include"mainwindow.h"

static void msgHandlerFunction(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  QMetaObject::invokeMethod(MsgHandlerWapper::instance(), "message", Q_ARG(QtMsgType,QString, msg));
}


int main(int argc,char * argv[])
{
  QApplication app(argc,argv);
  qRegisterMetaType<QtMsgType>("QtMsgType");
  qInstallMessageHandler(msgHandlerFunction);
  MainWindow main;
  main.show();
  return app.exec();
}
