const { app, BrowserWindow,Menu } = require('electron')
const path = require('path')
const url = require('url')
const ipc = require('electron').ipcMain
function createWindow () {
    const win = new BrowserWindow({
        width: 600,
        height: 510,
        webPreferences: {
            nodeIntegration: true,
            enableRemoteModule:true
        },
    })
    win.loadFile('index.html')
    Menu.setApplicationMenu(null)
    //开发者选项
    //win.webContents.openDevTools()
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



