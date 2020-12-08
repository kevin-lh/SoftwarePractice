const { app, BrowserWindow,Menu } = require('electron')
const path = require('path')
const url = require('url')

function createWindow () {
    const win = new BrowserWindow({
        width: 750,
        height: 600,
        webPreferences: {
            nodeIntegration: true,
            enableRemoteModule:true
        },

    })
    win.loadFile('../Model/index.html')
    //
    const mainMenu = Menu.buildFromTemplate(Menus);
    Menu.setApplicationMenu(mainMenu);
    //开发者选项
    //win.webContents.openDevTools()
}
function createWindowHelp () {
    const win = new BrowserWindow({
        width: 500,
        height: 400,
        webPreferences: {
            nodeIntegration: true,
            enableRemoteModule:true
        },
    })
    win.loadFile('../Model/help.html')
    //开发者选项
    //win.webContents.openDevTools()
    //Menu.setApplicationMenu(null)//取消菜单栏
}
app.commandLine.appendSwitch('ignore-certificate-errors');
app.whenReady().then(createWindow)
//Menu.setApplicationMenu(null)//取消菜单栏
app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit()
    }
})
app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
        createWindow()
    }
})
const Menus = [
    {
        label:'退出游戏',
        submenu:[{
            label:'退出游戏',
            role:'exit',
            click:function () {
                app.quit();
            }
        }]
    },
    {
        label: '帮助',
        role:'help',
        click:function () {
            createWindowHelp();
        }
    },
    {
        label: '重新开始',
        role:'reload',
        click:function () {
            app.relaunch();
        }
    }
];


