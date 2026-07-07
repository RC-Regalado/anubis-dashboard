import { createRouter, createWebHistory } from 'vue-router'
import FinanceDashboardView from '@/views/FinanceDashboardView.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'Dashboard',
      component: FinanceDashboardView,
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
      path: '/utils',
      name: 'Utils',
      component: () => import('@/views/UtilsView.vue'),
    },
    {
      path: '/upload',
      name: 'Uploads',
      component: () => import('@/components/Upload.vue'),
    },
  ],
})

export default router
