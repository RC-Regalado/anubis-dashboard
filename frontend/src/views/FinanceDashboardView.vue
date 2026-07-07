<template>
  <DashboardLayout>
    <template #actions>
      <div class="actions">
        <button
          class="btn btn-success"
          type="button"
          :disabled="syncing"
          @click="syncToServer"
        >
          {{ syncing ? 'Sincronizando...' : 'Sincronizar' }}
        </button>
        <button class="btn btn-primary" type="button" @click="openModal('transaction')">
          Nueva transaccion
        </button>
        <button class="btn btn-outline-secondary" type="button" @click="openModal('account')">
          Cuenta
        </button>
        <button class="btn btn-outline-secondary" type="button" @click="openModal('creditCard')">
          Tarjeta
        </button>
        <button class="btn btn-outline-secondary" type="button" @click="openModal('budget')">
          Presupuesto
        </button>
        <button class="btn btn-outline-secondary" type="button" @click="openModal('goal')">
          Meta
        </button>
      </div>
      <p v-if="syncMessage" class="sync-message" :class="`sync-message--${syncStatus}`">
        {{ syncMessage }}
      </p>
    </template>

    <SummaryCards />

    <section class="dashboard-grid dashboard-grid--primary">
      <CashflowChart />
      <CategoryExpenseChart />
    </section>

    <section class="dashboard-grid dashboard-grid--secondary">
      <CreditCardUsage />
      <GoalsProgress />
      <BudgetOverview />
      <AccountsOverview />
    </section>

    <RecentTransactions />

    <BaseModal v-model="modalOpen" :title="modalTitle">
      <TransactionForm v-if="activeModal === 'transaction'" @saved="closeModal" />
      <AccountForm v-if="activeModal === 'account'" @saved="closeModal" />
      <CreditCardForm v-if="activeModal === 'creditCard'" @saved="closeModal" />
      <BudgetForm v-if="activeModal === 'budget'" @saved="closeModal" />
      <GoalForm v-if="activeModal === 'goal'" @saved="closeModal" />
    </BaseModal>
  </DashboardLayout>
</template>

<script setup lang="ts">
import { computed, ref } from 'vue'
import DashboardLayout from '@/components/dashboard/DashboardLayout.vue'
import SummaryCards from '@/components/dashboard/SummaryCards.vue'
import CashflowChart from '@/components/dashboard/CashflowChart.vue'
import CategoryExpenseChart from '@/components/dashboard/CategoryExpenseChart.vue'
import CreditCardUsage from '@/components/dashboard/CreditCardUsage.vue'
import GoalsProgress from '@/components/dashboard/GoalsProgress.vue'
import BudgetOverview from '@/components/dashboard/BudgetOverview.vue'
import AccountsOverview from '@/components/dashboard/AccountsOverview.vue'
import RecentTransactions from '@/components/dashboard/RecentTransactions.vue'
import BaseModal from '@/components/ui/BaseModal.vue'
import TransactionForm from '@/components/forms/TransactionForm.vue'
import AccountForm from '@/components/forms/AccountForm.vue'
import CreditCardForm from '@/components/forms/CreditCardForm.vue'
import BudgetForm from '@/components/forms/BudgetForm.vue'
import GoalForm from '@/components/forms/GoalForm.vue'
import api from '@/api'
import { useFinanceStore } from '@/stores/financeStore'

type ModalType = 'transaction' | 'account' | 'creditCard' | 'budget' | 'goal'

const activeModal = ref<ModalType>('transaction')
const modalOpen = ref(false)
const syncing = ref(false)
const syncStatus = ref<'idle' | 'success' | 'error'>('idle')
const syncMessage = ref('')
const financeStore = useFinanceStore()

const modalTitle = computed(() => {
  const labels: Record<ModalType, string> = {
    transaction: 'Nueva transaccion',
    account: 'Nueva cuenta',
    creditCard: 'Nueva tarjeta',
    budget: 'Nuevo presupuesto',
    goal: 'Nueva meta financiera',
  }

  return labels[activeModal.value]
})

function openModal(type: ModalType) {
  activeModal.value = type
  modalOpen.value = true
}

function closeModal() {
  modalOpen.value = false
}

async function syncToServer() {
  syncing.value = true
  syncStatus.value = 'idle'
  syncMessage.value = ''

  try {
    financeStore.persistFinanceState()
    const ok = await api.syncFinanceData(financeStore.getSnapshot())
    syncStatus.value = ok ? 'success' : 'error'
    syncMessage.value = ok
      ? 'Datos financieros sincronizados.'
      : 'No se pudo sincronizar con el servidor.'
  } catch (error) {
    console.error(error)
    syncStatus.value = 'error'
    syncMessage.value = 'Error enviando datos financieros.'
  } finally {
    syncing.value = false
  }
}
</script>

<style scoped lang="scss">
.actions {
  display: flex;
  flex-wrap: wrap;
  gap: 0.5rem;
  justify-content: flex-end;
}

.sync-message {
  width: 100%;
  margin: 0.35rem 0 0;
  text-align: right;
  color: #607089;
  font-size: 0.9rem;
}

.sync-message--success {
  color: #168a52;
}

.sync-message--error {
  color: #c2413d;
}

.dashboard-grid {
  display: grid;
  gap: 1rem;
}

.dashboard-grid--primary {
  grid-template-columns: minmax(0, 1.25fr) minmax(320px, 0.75fr);
}

.dashboard-grid--secondary {
  grid-template-columns: repeat(4, minmax(0, 1fr));
}

@media (max-width: 1280px) {
  .dashboard-grid--secondary {
    grid-template-columns: repeat(2, minmax(0, 1fr));
  }
}

@media (max-width: 900px) {
  .dashboard-grid--primary,
  .dashboard-grid--secondary {
    grid-template-columns: 1fr;
  }

  .actions {
    justify-content: flex-start;
  }

  .sync-message {
    text-align: left;
  }
}
</style>
