<template>
  <section class="dashboard">
    <header class="hero">
      <div>
        <p class="hero__eyebrow">Dashboard</p>
        <h1 class="hero__title">Finanzas</h1>
        <p class="hero__copy">Gastos mensuales</p>
      </div>
      <div class="hero__actions">
        <button class="btn btn-info text-white" @click="xsetoff">Apagar pantalla</button>
      </div>
    </header>

    <section class="summary-grid">
      <article v-for="item in summaryCards" :key="item.label" class="summary-card">
        <p class="summary-card__label">{{ item.label }}</p>
        <p class="summary-card__value">{{ formatCurrency(item.value) }}</p>
      </article>
    </section>

    <section class="workspace">
      <article class="composer panel">
        <div class="panel__head">
          <div>
            <p class="panel__eyebrow">Registrar</p>
            <h2 class="panel__title">Entrada</h2>
          </div>
          <select v-model="activeCategory" class="form-select">
            <option v-for="section in sections" :key="section.id" :value="section.id">
              {{ section.label }}
            </option>
          </select>
        </div>

        <form class="composer__form" @submit.prevent="addEntry">
          <label class="field">
            <span>Titulo</span>
            <input
              v-model="draft.title"
              class="form-control"
              placeholder="Salida, Café, Gas..."
              required
            />
          </label>

          <label class="field">
            <span>{{ currentSection.amountLabel }}</span>
            <input
              v-model.number="draft.amount"
              class="form-control"
              min="0"
              step="0.01"
              type="number"
              required
            />
          </label>

          <label class="field">
            <span>{{ currentSection.accountLabel }}</span>
            <input
              v-model="draft.account"
              class="form-control"
              :placeholder="currentSection.accountPlaceholder"
            />
          </label>

          <label class="field">
            <span>{{ currentSection.counterpartyLabel }}</span>
            <input
              v-model="draft.counterparty"
              class="form-control"
              :placeholder="currentSection.counterpartyPlaceholder"
            />
          </label>

          <label class="field">
            <span>Fecha</span>
            <input v-model="draft.date" class="form-control" type="date" />
          </label>

          <label class="field">
            <span>Estado</span>
            <select v-model="draft.status" class="form-select">
              <option value="planned">Planeado</option>
              <option value="active">Activo</option>
              <option value="paid">Pagado</option>
              <option value="cleared">Liquidado</option>
            </select>
          </label>

          <label class="field field--full">
            <span>Notas</span>
            <textarea
              v-model="draft.note"
              class="form-control"
              rows="4"
              placeholder="Un poco de contexto..."
            ></textarea>
          </label>

          <div class="composer__footer">
            <button class="btn btn-success" type="submit">
              Agregar a {{ currentSection.label }}
            </button>
          </div>
        </form>
      </article>

      <article class="ledger panel">
        <div class="panel__head">
          <div>
            <h2 class="panel__title">Movimientos</h2>
          </div>
        </div>

        <div class="category-list">
          <button
            v-for="section in sections"
            :key="section.id"
            class="category-pill"
            :class="{ 'category-pill--active': activeCategory === section.id }"
            @click="activeCategory = section.id"
          >
            <span>{{ section.label }}</span>
            <strong>{{ entriesByCategory(section.id).length }}</strong>
          </button>
        </div>

        <div class="ledger__stats">
          <div class="ledger__stat">
            <span>Total</span>
            <strong>{{ formatCurrency(categoryTotal) }}</strong>
          </div>
          <div class="ledger__stat">
            <span>Entradas</span>
            <strong>{{ activeEntries.length }}</strong>
          </div>
        </div>

        <div class="ledger__table-wrap">
          <table class="table ledger__table">
            <thead>
              <tr>
                <th>Titulo</th>
                <th>Monto</th>
                <th>Cuenta</th>
                <th>Banco</th>
                <th>Fecha</th>
                <th>Estado</th>
                <th></th>
              </tr>
            </thead>
            <tbody v-if="activeEntries.length">
              <tr v-for="entry in activeEntries" :key="entry.id">
                <td>
                  <strong>{{ entry.title }}</strong>
                  <p v-if="entry.note" class="ledger__note">{{ entry.note }}</p>
                </td>
                <td>{{ formatCurrency(entry.amount) }}</td>
                <td>{{ entry.account || '-' }}</td>
                <td>{{ entry.counterparty || '-' }}</td>
                <td>{{ entry.date || '-' }}</td>
                <td>
                  <span class="status-chip">{{ entry.status }}</span>
                </td>
                <td class="text-end">
                  <button class="btn btn-sm btn-outline-danger" @click="removeEntry(entry.id)">
                    Borrar
                  </button>
                </td>
              </tr>
            </tbody>
            <tbody v-else>
              <tr>
                <td colspan="7" class="ledger__empty">Aun no hay datos</td>
              </tr>
            </tbody>
          </table>
        </div>
      </article>
    </section>
  </section>
</template>

<script lang="ts">
import { computed, defineComponent, reactive, ref, watch } from 'vue'

type CategoryId =
  | 'tarjetas'
  | 'debts'
  | 'cuentas'
  | 'trx'
  | 'ahorros'
  | 'ingresos'
  | 'egresos'
  | 'pagos'

interface FinanceEntry {
  id: string
  category: CategoryId
  title: string
  amount: number
  account: string
  counterparty: string
  date: string
  status: string
  note: string
}

interface SectionMeta {
  id: CategoryId
  label: string
  amountLabel: string
  accountLabel: string
  accountPlaceholder: string
  counterpartyLabel: string
  counterpartyPlaceholder: string
}

const STORAGE_KEY = 'sync-finance-tracker'

const sections: SectionMeta[] = [
  {
    id: 'cards',
    label: 'Tarjetas',
    amountLabel: 'Saldo Actual',
    accountLabel: 'Tarjeta',
    accountPlaceholder: 'Visa Platinum',
    counterpartyLabel: '',
    counterpartyPlaceholder: 'Bank or provider',
  },
  {
    id: 'debts',
    label: 'Deudas',
    amountLabel: 'Salida',
    accountLabel: 'Prestamo',
    accountPlaceholder: 'Prestamo personal',
    counterpartyLabel: 'Institucion',
    counterpartyPlaceholder: 'Banco',
  },
  {
    id: 'accounts',
    label: 'Cuentas',
    amountLabel: 'Saldo disponible',
    accountLabel: 'Cuenta',
    accountPlaceholder: 'Nombre cuenta',
    counterpartyLabel: 'Institucion',
    counterpartyPlaceholder: 'Banco',
  },
  {
    id: 'transfers',
    label: 'TRX',
    amountLabel: 'Monto transferencia',
    accountLabel: 'Desde',
    accountPlaceholder: 'Cuenta',
    counterpartyLabel: 'Para',
    counterpartyPlaceholder: 'Cuenta',
  },
  {
    id: 'savings',
    label: 'Ahorros',
    amountLabel: 'Saved amount',
    accountLabel: 'Saving goal',
    accountPlaceholder: 'Emergency fund',
    counterpartyLabel: 'Destination',
    counterpartyPlaceholder: 'Bank or wallet',
  },
  {
    id: 'incomes',
    label: 'Ingresos',
    amountLabel: 'Income amount',
    accountLabel: 'Received in',
    accountPlaceholder: 'Checking account',
    counterpartyLabel: 'Source',
    counterpartyPlaceholder: 'Employer or client',
  },
  {
    id: 'outcomes',
    label: 'Gastos',
    amountLabel: 'Expense amount',
    accountLabel: 'Paid from',
    accountPlaceholder: 'Cash or account',
    counterpartyLabel: 'Vendor',
    counterpartyPlaceholder: 'Store, service, person',
  },
  {
    id: 'payments',
    label: 'Pagos',
    amountLabel: 'Payment amount',
    accountLabel: 'Payment account',
    accountPlaceholder: 'Credit card payment',
    counterpartyLabel: 'Recipient',
    counterpartyPlaceholder: 'Bank, landlord, vendor',
  },
]

function loadEntries(): FinanceEntry[] {
  const raw = localStorage.getItem(STORAGE_KEY)

  if (!raw) {
    return []
  }

  try {
    return JSON.parse(raw) as FinanceEntry[]
  } catch (error) {
    console.error(error)
    return []
  }
}

function createDraft() {
  return {
    title: '',
    amount: 0,
    account: '',
    counterparty: '',
    date: '',
    status: 'active',
    note: '',
  }
}

export default defineComponent({
  name: 'FinanceDashboard',
  setup() {
    const entries = ref<FinanceEntry[]>(loadEntries())
    const activeCategory = ref<CategoryId>('accounts')
    const draft = reactive(createDraft())

    const currentSection = computed(
      () => sections.find((section) => section.id === activeCategory.value) ?? sections[0],
    )

    const activeEntries = computed(() =>
      entries.value.filter((entry) => entry.category === activeCategory.value),
    )

    const categoryTotal = computed(() =>
      activeEntries.value.reduce((total, entry) => total + entry.amount, 0),
    )

    const sumByCategory = (category: CategoryId) =>
      entries.value
        .filter((entry) => entry.category === category)
        .reduce((total, entry) => total + entry.amount, 0)

    const summaryCards = computed(() => {
      const incomes = sumByCategory('incomes')
      const outcomes = sumByCategory('outcomes')
      const debts = sumByCategory('debts')
      const savings = sumByCategory('savings')
      const accounts = sumByCategory('accounts')

      return [
        { label: 'Neto disponible', value: incomes - outcomes },
        { label: 'En cuenta', value: accounts },
        { label: 'Ahorros', value: savings },
        { label: 'Deuda', value: debts },
      ]
    })

    watch(
      entries,
      (value) => {
        localStorage.setItem(STORAGE_KEY, JSON.stringify(value))
      },
      { deep: true },
    )

    const addEntry = () => {
      entries.value.unshift({
        id: `${activeCategory.value}-${Date.now()}`,
        category: activeCategory.value,
        title: draft.title.trim(),
        amount: Number(draft.amount),
        account: draft.account.trim(),
        counterparty: draft.counterparty.trim(),
        date: draft.date,
        status: draft.status,
        note: draft.note.trim(),
      })

      Object.assign(draft, createDraft())
    }

    const removeEntry = (id: string) => {
      entries.value = entries.value.filter((entry) => entry.id !== id)
    }

    const entriesByCategory = (category: CategoryId) =>
      entries.value.filter((entry) => entry.category === category)

    const clearAll = () => {
      entries.value = []
      localStorage.removeItem(STORAGE_KEY)
    }

    const seedDemoData = () => {
      entries.value = [
        {
          id: 'accounts-1',
          category: 'accounts',
          title: 'Main checking',
          amount: 2850,
          account: 'Checking',
          counterparty: 'Banco Azul',
          date: '2026-04-06',
          status: 'active',
          note: 'Primary operating account',
        },
        {
          id: 'savings-1',
          category: 'savings',
          title: 'Emergency fund',
          amount: 4300,
          account: 'Emergency',
          counterparty: 'High yield',
          date: '2026-04-03',
          status: 'active',
          note: '6 months target in progress',
        },
        {
          id: 'incomes-1',
          category: 'incomes',
          title: 'Salary',
          amount: 3200,
          account: 'Checking',
          counterparty: 'Employer',
          date: '2026-04-01',
          status: 'cleared',
          note: 'Monthly payroll',
        },
        {
          id: 'outcomes-1',
          category: 'outcomes',
          title: 'Groceries',
          amount: 180,
          account: 'Credit card',
          counterparty: 'Market',
          date: '2026-04-05',
          status: 'paid',
          note: 'Weekly food budget',
        },
        {
          id: 'payments-1',
          category: 'payments',
          title: 'Rent',
          amount: 950,
          account: 'Checking',
          counterparty: 'Landlord',
          date: '2026-04-02',
          status: 'paid',
          note: 'April payment',
        },
        {
          id: 'debts-1',
          category: 'debts',
          title: 'Car loan',
          amount: 7800,
          account: 'Installment plan',
          counterparty: 'Credit union',
          date: '2026-04-01',
          status: 'active',
          note: '18 payments remaining',
        },
      ]
    }

    const formatCurrency = (value: number) =>
      new Intl.NumberFormat('en-US', {
        style: 'currency',
        currency: 'USD',
        maximumFractionDigits: 2,
      }).format(value || 0)

    const xsetoff = async () => {
      const response = await api.screenOff()

      if (response) {
        console.debug(response.data)
      }
    }

    return {
      activeCategory,
      activeEntries,
      addEntry,
      categoryTotal,
      clearAll,
      currentSection,
      draft,
      entriesByCategory,
      formatCurrency,
      removeEntry,
      sections,
      seedDemoData,
      summaryCards,
      xsetoff,
    }
  },
})
</script>

<style scoped lang="scss">
.dashboard {
  display: grid;
  gap: 1.5rem;
}

.hero {
  display: flex;
  justify-content: space-between;
  gap: 1.5rem;
  align-items: flex-end;
  padding: 1.8rem;
  border-radius: 1.6rem;
  background: linear-gradient(135deg, rgba(12, 90, 73, 0.98), rgba(16, 35, 61, 0.96));
  color: #ffffff;
  box-shadow: 0 24px 60px rgba(16, 35, 61, 0.2);
}

.hero__eyebrow,
.panel__eyebrow {
  margin: 0 0 0.35rem;
  text-transform: uppercase;
  letter-spacing: 0.14em;
  font-size: 0.75rem;
  font-weight: 700;
}

.hero__title,
.panel__title {
  margin: 0;
  font-size: clamp(1.8rem, 3vw, 2.75rem);
}

.hero__copy {
  max-width: 40rem;
  margin: 0.75rem 0 0;
  color: rgba(255, 255, 255, 0.74);
}

.hero__actions {
  display: flex;
  flex-wrap: wrap;
  gap: 0.75rem;
}

.summary-grid {
  display: grid;
  grid-template-columns: repeat(4, minmax(0, 1fr));
  gap: 1rem;
}

.summary-card,
.panel {
  background: var(--panel-bg);
  border: 1px solid var(--panel-border);
  border-radius: 1.5rem;
  backdrop-filter: blur(18px);
  box-shadow: 0 18px 50px rgba(16, 35, 61, 0.08);
}

.summary-card {
  padding: 1.2rem;
}

.summary-card__label {
  margin: 0;
  color: var(--ink-soft);
  font-weight: 600;
}

.summary-card__value {
  margin: 0.5rem 0 0;
  font-size: 1.8rem;
  font-weight: 700;
}

.workspace {
  display: grid;
  grid-template-columns: minmax(0, 420px) minmax(0, 1fr);
  gap: 1.5rem;
}

.panel {
  padding: 1.4rem;
}

.panel__head {
  display: flex;
  justify-content: space-between;
  gap: 1rem;
  align-items: flex-start;
  margin-bottom: 1.25rem;
}

.panel__title {
  font-size: 1.5rem;
}

.composer__form {
  display: grid;
  grid-template-columns: repeat(2, minmax(0, 1fr));
  gap: 1rem;
}

.field {
  display: grid;
  gap: 0.45rem;
}

.field span {
  font-weight: 600;
}

.field--full {
  grid-column: 1 / -1;
}

.composer__footer {
  grid-column: 1 / -1;
  display: flex;
  justify-content: space-between;
  gap: 1rem;
  align-items: center;
}

.composer__hint {
  margin: 0;
  color: var(--ink-soft);
}

.category-list {
  display: flex;
  flex-wrap: wrap;
  gap: 0.75rem;
  margin-bottom: 1rem;
}

.category-pill {
  display: flex;
  align-items: center;
  gap: 0.65rem;
  border: 1px solid rgba(16, 35, 61, 0.1);
  background: #ffffff;
  color: var(--ink-strong);
  border-radius: 999px;
  padding: 0.65rem 0.9rem;
}

.category-pill strong {
  display: inline-flex;
  align-items: center;
  justify-content: center;
  min-width: 1.8rem;
  height: 1.8rem;
  border-radius: 999px;
  background: rgba(17, 122, 101, 0.1);
  color: var(--accent-deep);
}

.category-pill--active {
  border-color: rgba(17, 122, 101, 0.28);
  background: rgba(17, 122, 101, 0.08);
}

.ledger__stats {
  display: flex;
  gap: 1rem;
  margin-bottom: 1rem;
}

.ledger__stat {
  flex: 1;
  padding: 1rem;
  border-radius: 1rem;
  background: rgba(16, 35, 61, 0.04);
}

.ledger__stat span {
  display: block;
  color: var(--ink-soft);
}

.ledger__stat strong {
  font-size: 1.35rem;
}

.ledger__table-wrap {
  overflow-x: auto;
}

.ledger__table {
  margin-bottom: 0;
}

.ledger__note {
  margin: 0.35rem 0 0;
  color: var(--ink-soft);
}

.status-chip {
  display: inline-flex;
  padding: 0.25rem 0.6rem;
  border-radius: 999px;
  background: rgba(17, 122, 101, 0.12);
  color: var(--accent-deep);
  text-transform: capitalize;
}

.ledger__empty {
  padding: 2rem 1rem;
  color: var(--ink-soft);
  text-align: center;
}

@media (max-width: 1199px) {
  .summary-grid {
    grid-template-columns: repeat(2, minmax(0, 1fr));
  }

  .workspace {
    grid-template-columns: 1fr;
  }
}

@media (max-width: 767px) {
  .hero,
  .panel__head,
  .composer__footer {
    flex-direction: column;
    align-items: stretch;
  }

  .summary-grid,
  .composer__form {
    grid-template-columns: 1fr;
  }

  .ledger__stats {
    flex-direction: column;
  }
}
</style>
