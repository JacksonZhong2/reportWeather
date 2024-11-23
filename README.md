## Noob使用C++Qt编写的天气预报项目
# 项目介绍
这是一款简易的天气预报软件，可查看国内城市近七日天气情况

该项目从[天气API](http://www.tianqiapi.com/)提供的 API 接口中获取 JSON 数据，使用 QT 提供的类来解析 JSON 数据并显示在项目上；发送 HTTP 请求，获得天气数据；自行绘制温度曲线和查看当前天气，所有天气图表都有显示；可以搜索中国所有城市天气预报；查看穿衣指数、空气质量、未来7天空气、风力风向和最高最低温度；无边框窗口；重写了鼠标移动事件，窗口可跟随鼠标移动；右键菜单退出功能；
## 不足
1. 城市显示有问题，当搜索县、区等城市，任然显示xx市，而不是xx县
2. 退出按钮待优化
# 效果演示
![828c57f51451fe3d59b2b11d363b428](https://github.com/user-attachments/assets/43cc1e5f-7927-49f8-a7f1-fa4317927fde)
![image](https://github.com/user-attachments/assets/67932314-1a11-4c23-bf82-5a2f61c6d501)
