
## 总体步骤

先根据需求设计出静态的组件和效果，使用静态的数据，props

npx create-react-app my-app

占位用的图片，极好的
http://placeimg.com/1200/800/nature


## 数据的设计

尽量使用 props，而不是 state。交互时才需要 state

![[不活跃主题/misc/_attachments/通过问自己以下三个问题，你可以逐个检查相应数据是否属于 state：.png]]

react 的数据流向是单向（父到子）的，因此将 state 放在父组件中。

子组建通过父组件传入的函数来改变父组件的 state


## 部署

flask 默认将其下的 static 文件夹映射到 /static 路由
react 在 build 之后，index.html 文件位于其 build 文件夹下
部署方法：将 react 依赖的所有静态资源都放到 public/static 文件夹下，修改 public/index.html 文件，使用 PUBLIC_URL 这种相对路径

![[不活跃主题/misc/_attachments/frontend.png|200]]

npm run build 之后，将 build/index.html 放到 flask 的 templates 文件夹中，build/static 的内容放到 flask 的 static 文件夹中
通过 package.json 的 prebuild 和 postbuild 来完成部署

![[不活跃主题/misc/_attachments/LON eact-scrlets start,.png|400]]

![[不活跃主题/misc/_attachments/static.png|200]]


```cardlink
url: https://legacy.reactjs.org/docs/getting-started.html
title: "Getting Started – React"
description: "A JavaScript library for building user interfaces"
host: legacy.reactjs.org
favicon: /favicon.ico
image: https://reactjs.org/logo-og.png
```



```cardlink
url: https://create-react-app.dev/docs/using-global-variables/
title: "Using Global Variables | Create React App"
description: "When you include a script in the HTML file that defines global variables and try to use one of these variables in the code, the linter will complain because it cannot see the definition of the variable."
host: create-react-app.dev
favicon: /img/favicon/favicon.ico
image: https://create-react-app.dev/img/logo-og.png
```



```cardlink
url: https://create-react-app.dev/docs/using-the-public-folder/
title: "Using the Public Folder | Create React App"
description: "Note: this feature is available with react-scripts@0.5.0 and higher."
host: create-react-app.dev
favicon: /img/favicon/favicon.ico
image: https://create-react-app.dev/img/logo-og.png
```



```cardlink
url: https://react-bootstrap.github.io/components/cards/
title: "React-Bootstrap"
description: "The most popular front-end framework, rebuilt for React."
host: react-bootstrap.github.io
```



```cardlink
url: https://github.com/axios/axios
title: "GitHub - axios/axios: Promise based HTTP client for the browser and node.js"
description: "Promise based HTTP client for the browser and node.js - GitHub - axios/axios: Promise based HTTP client for the browser and node.js"
host: github.com
favicon: https://github.githubassets.com/favicons/favicon.svg
image: https://opengraph.githubassets.com/c6056672c90e944cf69300552d9dbfee770cc0e40f54ab60c3edff88aea2ed1b/axios/axios
```


