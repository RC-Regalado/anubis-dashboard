import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import 'bootstrap/dist/css/bootstrap.css'
//import "./assets/scss/app.scss";

const app = createApp(App)

app.use(router)

app.mount('#app')
