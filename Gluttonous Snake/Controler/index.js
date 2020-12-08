//控制游戏主逻辑
class Game {
    constructor(id, snake,food) {
        //选择地图对象
        this.map = document.querySelector(id);
        this.rows = 25;
        this.columns = 25;
        this.size = 20;

        //得分，初始得分0
        this.score = 0;
        //关卡
        this.level = 1;
        //缓存地图信息
        this.maps = [];
        //挂载蛇对象
        this.snake = snake;
        //挂载食物对象
        this.food = food;
        //定时器对象
        this.timer = null;
        //速度
        this.speed = 250;
        this.init();

    }

    init() {
        //增加地图样式
        this.addMapStyle();
        //渲染地图
        this.renderMap();

        //渲染蛇
        this.renderSnake();

        //随机食物坐标
        this.randomFood();

        //根据随机食物坐标渲染食物
        this.renderFood();

        //得分
        this.renderSocre();
        //关卡
        this.renderLevel();
        //键盘绑定事件
        this.bindEvent();
    }



    addMapStyle() {
        this.map.className = 'game';
        this.map.style.width = this.columns * this.size + 'px';
        this.map.style.height = this.rows * this.size + 'px';
    }

    renderMap() {
        for (let i = 0; i < this.rows; i++) {
            //创建行
            let row = document.createElement('div');
            row.className = 'row';
            //缓存地图坐标信息
            let arr = [];
            for (let j = 0; j < this.rows; j++) {
                //创建列
                let column = document.createElement('div');
                column.className = 'column';
                //列装到行里面
                row.appendChild(column);
                arr.push(column);
            }
            //行加到列上面
            this.map.appendChild(row);
            this.maps.push(arr);
        }
    }
    renderSnake() {
        //准备地图的坐标信息,找蛇头、蛇身坐标改变颜色
        for (let i = 0; i < this.snake.length; i++) {
            this.maps[this.snake[i].row][this.snake[i].column].style.backgroundColor = i === 0 ? 'rgba(60, 63, 65)' : 'rgba(105, 198, 109)';
        }
    }
    randomFood(){
        //floor向下取整，因为random为【0,1】，最大0.99，向下取整为19
        let row = Math.floor(Math.random()*25);
        let column = Math.floor(Math.random()*25);
        //判断食物坐标是否和蛇头坐标重合
        if(row === this.snake[0].row && column === this.snake[0].column){
            this.randomFood();
            return false;
        }
        this.food.row = row;
        this.food.column = column;
    }
    renderFood(){
        //准备地图的坐标信息,找食物坐标改变颜色
        var r = Math.floor(Math.random() * 256);
        var g = Math.floor(Math.random() * 256);
        var b = Math.floor(Math.random() * 256);
        var RGB = 'rgb(' + r + ',' + g + ',' + b + ')';
        this.maps[this.food.row][this.food.column].style.backgroundColor = RGB;
    }

    start() {
        //让蛇跑起来
        this.timer = setInterval(() => {
            this.snake.move();

            //判断是否撞墙 以及 是否碰到蛇尾巴
            if (this.knockedEdge() || this.snake.killSelf()) {
                alert("Game Over ！！！");
                this.gameOver();
                return;

            }
            //蛇吃食物
            if(this.isEatFood()){
                //1、蛇身体增长
                this.snake.growUp();
                //2、更新食物坐标
                this.randomFood();

                //3、更新关卡
                this.renderLevel();
            }

            //清除之前的坐标信息
            this.clear();
            //根据蛇的最新坐标，重新渲染
            this.renderSnake();
            //重新渲染食物
            this.renderFood();
        }, this.speed);
    }

    bindEvent() {
        window.addEventListener('keydown', (...args) => {
            let kc = args[0].keyCode;//获取键码
            //改变direction的值
            this.snake.changeDirection(kc);
        });
    }

    clear() {
        for (let i = 0; i < this.maps.length; i++) {
            for (let j = 0; j < this.maps[i].length; j++) {
                //清空每一个column的背景颜色
                this.maps[i][j].style.backgroundColor = '';
            }
        }
    }

    knockedEdge() {
        //判断蛇头的信息是否超出地图
        if (this.snake[0].row < 0 || this.snake[0].row > 24 || this.snake[0].column < 0 || this.snake[0].column > 24) {
            return true;
        }
    }

    isEatFood(){
        if(this.snake[0].row === this.food.row && this.snake[0].column === this.food.column){
            this.score++;
            this.renderSocre();
            switch (this.score) {
                case 5: this.level=2;this.speed=200;this.start();return ;
                case 10: this.level=3;this.speed=160;this.start();return ;
                case 15: this.level=4;this.speed=140;this.start();return ;
            }
            console.log(this.level);
            return true;
        }
    }
    renderSocre(){
        document.getElementById("scoree").innerHTML = this.score;
    }
    renderLevel(){
        document.getElementById("level").innerHTML = this.level;
    }

    gameOver() {
        //停止游戏，清除定时器
        //alert('撞墙啦！');
        clearInterval(this.timer);

    }

}
//蛇
//继承数组类，使用pop方法
class Snake extends Array{
    constructor() {
        super();
        //蛇头坐标
        this[0]={row:10,column:10};
        //蛇身体
        this[1]={row:10,column:9};
        this[2]={row:10,column:8};
        this.length = 3;

        //键盘键码
        this.direction = 39; //39 代表右键
    }
    move(){
        //1 去掉蛇尾
        this.tail = this.pop();
        //2 蛇头移动 根据键盘按下的键
        if(this.direction === 39){
            //往右跑
            this.unshift({
                row:this[0].row,
                column:this[0].column+1
            });
        }else if(this.direction === 37){
            //往左跑
            this.unshift({
                row:this[0].row,
                column:this[0].column-1
            });
        }else if(this.direction === 40){
            //往下跑
            this.unshift({
                row:this[0].row+1,
                column:this[0].column
            });
        }else if (this.direction === 38){
            //往下跑
            this.unshift({
                row:this[0].row-1,
                column:this[0].column
            });
        }
    }
    changeDirection(direction){
        //右 39 左 37
        let res = Math.abs(this.direction-direction);
        //如果向右跑按下左，向上跑按下，或者撞墙了还按
        if(res == 2||res==0){
            return;
        }
        this.direction = direction;
    }

    killSelf(){
        //碰到蛇身体
        for(let i= 1 ;i < this.length;i++){
            if(this[0].row === this[i].row && this[0].column === this[i].column){
                return true;
            }
        }
    }
    growUp(){
        //把move时候干掉的蛇尾巴加回来
        this.push(this.tail);

    }

}

//食物类
class Food {
    constructor(row = 0,column = 0) {
        //食物的坐标信息
        this.row = row;
        this.column = column;
    }
    
}
game = new Game('#game',new Snake(),new Food());
//开始
function ifStart() {
   game.start();
}
//暂停
function pause() {
    clearInterval(game.timer);
}
//重载
function reload() {
    app.quit();
}
//模式选择
function easy() {
    game.speed = 250;
}
function normal() {
    game.speed = 200;
}
function hard() {
    game.speed = 100;
}