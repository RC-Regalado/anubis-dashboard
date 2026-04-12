import { createRouter, createWebHistory } from 'vue-router'
import DashboardView from '@/views/DashboardView.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'Dashboard',
      component: DashboardView,
    },
    {
      path: '/file',
      name: 'Files',
      component: () => import('../views/FilesView.vue'),
    },
    {
      path: '/notes',
      name: 'Notes',
      component: () => import('@/views/NotesView.vue'),
    },
    {
      path: '/upload',
      name: 'Uploads',
      component: () => import('@/components/Upload.vue'),
    },
  ],
})

export default router
