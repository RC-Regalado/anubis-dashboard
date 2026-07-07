import { computed, reactive, watch } from 'vue'

export type AccountType = 'cash' | 'bank' | 'savings' | 'investment' | 'credit_card' | 'loan'
export type TransactionType = 'income' | 'expense' | 'transfer' | 'card_payment' | 'fee'
export type TransactionStatus = 'pending' | 'cleared' | 'reconciled'

export interface Account {
  id: string
  name: string
  type: AccountType
  currency: string
  balance: number
}

export interface CreditCard {
  id: string
  name: string
  limit: number
  currentBalance: number
  closingDate: string
  dueDate: string
  accountId: string
}

export interface Transaction {
  id: string
  type: TransactionType
  amount: number
  date: string
  accountFromId: string
  accountToId: string
  creditCardId: string
  categoryId: string
  merchantId: string
  tags: string[]
  notes: string
  status: TransactionStatus
}

export interface Category {
  id: string
  name: string
  parentId: string
}

export interface Merchant {
  id: string
  name: string
}

export interface Budget {
  id: string
  categoryId: string
  month: string
  limitAmount: number
}

export interface Goal {
  id: string
  name: string
  targetAmount: number
  currentAmount: number
  dueDate: string
}

export interface TransactionInput {
  type: TransactionType
  amount: number
  date: string
  accountFromId: string
  accountToId: string
  creditCardId: string
  categoryId: string
  merchantId: string
  tags: string[]
  notes: string
  status: TransactionStatus
}

export interface FinanceState {
  accounts: Account[]
  creditCards: CreditCard[]
  transactions: Transaction[]
  categories: Category[]
  merchants: Merchant[]
  budgets: Budget[]
  goals: Goal[]
}

const STORAGE_KEY = 'sync-finance-dashboard'

const initialFinanceState = (): FinanceState => ({
  accounts: [],
  creditCards: [],
  categories: [
    { id: 'cat-income', name: 'Ingresos', parentId: '' },
    { id: 'cat-food', name: 'Comida', parentId: '' },
    { id: 'cat-home', name: 'Hogar', parentId: '' },
    { id: 'cat-transport', name: 'Transporte', parentId: '' },
    { id: 'cat-services', name: 'Servicios', parentId: '' },
    { id: 'cat-health', name: 'Salud', parentId: '' },
    { id: 'cat-fees', name: 'Comisiones', parentId: '' },
    { id: 'cat-tools', name: 'Herramientas', parentId: '' },
  ],
  merchants: [
    { id: 'mer-employer', name: 'Empresa' },
    { id: 'mer-market', name: 'Supermercado' },
    { id: 'mer-fuel', name: 'Gasolinera' },
    { id: 'mer-electricity', name: 'Energia' },
    { id: 'mer-bank', name: 'Banco' },
    { id: 'mer-pe', name: 'Panda Express' },
    { id: 'mer-cw', name: 'China Wok' },
    { id: 'mer-pizza', name: 'Pizza' },
    { id: 'mer-intel', name: 'Intelmax' },
    { id: 'mer-tools', name: 'Ferretería' },
  ],
  transactions: [],
  budgets: [],
  goals: [],
})

function loadFinanceState(): FinanceState {
  if (typeof localStorage === 'undefined') {
    return initialFinanceState()
  }

  const raw = localStorage.getItem(STORAGE_KEY)

  if (!raw) {
    return initialFinanceState()
  }

  try {
    return {
      ...initialFinanceState(),
      ...(JSON.parse(raw) as Partial<FinanceState>),
    }
  } catch (error) {
    console.error(error)
    return initialFinanceState()
  }
}

const state = reactive<FinanceState>(loadFinanceState())

function getSnapshot(): FinanceState {
  return {
    accounts: state.accounts.map((item) => ({ ...item })),
    creditCards: state.creditCards.map((item) => ({ ...item })),
    transactions: state.transactions.map((item) => ({ ...item, tags: [...item.tags] })),
    categories: state.categories.map((item) => ({ ...item })),
    merchants: state.merchants.map((item) => ({ ...item })),
    budgets: state.budgets.map((item) => ({ ...item })),
    goals: state.goals.map((item) => ({ ...item })),
  }
}

function persistFinanceState(): void {
  if (typeof localStorage === 'undefined') {
    return
  }

  localStorage.setItem(STORAGE_KEY, JSON.stringify(getSnapshot()))
}

watch(state, persistFinanceState, { deep: true })

const currentMonth = computed(() => new Date().toISOString().slice(0, 7))

const monthlyTransactions = computed(() =>
  state.transactions.filter((transaction) => transaction.date.startsWith(currentMonth.value)),
)

function positiveAmount(value: number): number {
  return Math.max(0, Number(value) || 0)
}

function createId(prefix: string): string {
  return `${prefix}-${Date.now()}-${Math.random().toString(36).slice(2, 7)}`
}

function categoryName(categoryId: string): string {
  return state.categories.find((category) => category.id === categoryId)?.name ?? 'Sin categoria'
}

function merchantName(merchantId: string): string {
  return state.merchants.find((merchant) => merchant.id === merchantId)?.name ?? ''
}

function accountName(accountId: string): string {
  return state.accounts.find((account) => account.id === accountId)?.name ?? ''
}

function cardName(cardId: string): string {
  return state.creditCards.find((card) => card.id === cardId)?.name ?? ''
}

function applyTransactionEffects(transaction: Transaction): void {
  const amount = positiveAmount(transaction.amount)

  if (transaction.type === 'income') {
    const account = state.accounts.find((item) => item.id === transaction.accountToId)
    if (account) account.balance += amount
    return
  }

  if (transaction.type === 'expense' || transaction.type === 'fee') {
    const account = state.accounts.find((item) => item.id === transaction.accountFromId)
    if (account) account.balance -= amount

    const card = state.creditCards.find((item) => item.id === transaction.creditCardId)
    if (card) card.currentBalance += amount
    return
  }

  if (transaction.type === 'transfer') {
    const from = state.accounts.find((item) => item.id === transaction.accountFromId)
    const to = state.accounts.find((item) => item.id === transaction.accountToId)
    if (from) from.balance -= amount
    if (to) to.balance += amount
    return
  }

  if (transaction.type === 'card_payment') {
    const account = state.accounts.find((item) => item.id === transaction.accountFromId)
    const card = state.creditCards.find((item) => item.id === transaction.creditCardId)
    if (account) account.balance -= amount
    if (card) card.currentBalance = Math.max(0, card.currentBalance - amount)
  }
}

const metrics = computed(() => {
  const monthlyIncome = monthlyTransactions.value
    .filter((transaction) => transaction.type === 'income')
    .reduce((total, transaction) => total + positiveAmount(transaction.amount), 0)

  const monthlyExpenses = monthlyTransactions.value
    .filter((transaction) => transaction.type === 'expense' || transaction.type === 'fee')
    .reduce((total, transaction) => total + positiveAmount(transaction.amount), 0)

  const savings = monthlyIncome - monthlyExpenses
  const debtTotal =
    state.creditCards.reduce((total, card) => total + positiveAmount(card.currentBalance), 0) +
    state.accounts
      .filter((account) => account.type === 'loan')
      .reduce((total, account) => total + positiveAmount(Math.abs(account.balance)), 0)

  const balanceTotal = state.accounts
    .filter((account) => account.type !== 'loan')
    .reduce((total, account) => total + account.balance, 0)

  return {
    balanceTotal,
    monthlyIncome,
    monthlyExpenses,
    monthlySavings: savings,
    debtTotal,
    savingsRate: monthlyIncome > 0 ? (savings / monthlyIncome) * 100 : 0,
  }
})

const categoryExpenses = computed(() => {
  const totals = new Map<string, number>()

  monthlyTransactions.value
    .filter((transaction) => transaction.type === 'expense' || transaction.type === 'fee')
    .forEach((transaction) => {
      const name = categoryName(transaction.categoryId)
      totals.set(name, (totals.get(name) ?? 0) + positiveAmount(transaction.amount))
    })

  return Array.from(totals.entries())
    .map(([name, amount]) => ({ name, amount }))
    .sort((left, right) => right.amount - left.amount)
})

const monthlyCashflow = computed(() => {
  const days = new Map<string, { date: string; income: number; expenses: number }>()

  monthlyTransactions.value.forEach((transaction) => {
    const date = transaction.date
    const day = days.get(date) ?? { date, income: 0, expenses: 0 }

    if (transaction.type === 'income') {
      day.income += positiveAmount(transaction.amount)
    }

    if (transaction.type === 'expense' || transaction.type === 'fee') {
      day.expenses += positiveAmount(transaction.amount)
    }

    days.set(date, day)
  })

  return Array.from(days.values()).sort((left, right) => left.date.localeCompare(right.date))
})

const recentTransactions = computed(() =>
  [...state.transactions]
    .sort((left, right) => right.date.localeCompare(left.date))
    .slice(0, 8)
    .map((transaction) => ({
      ...transaction,
      categoryName: categoryName(transaction.categoryId),
      merchantName: merchantName(transaction.merchantId),
      accountFromName: accountName(transaction.accountFromId),
      accountToName: accountName(transaction.accountToId),
      creditCardName: cardName(transaction.creditCardId),
    })),
)

const creditCardUsage = computed(() =>
  state.creditCards.map((card) => ({
    ...card,
    usageRate: card.limit > 0 ? (positiveAmount(card.currentBalance) / card.limit) * 100 : 0,
  })),
)

const goalsProgress = computed(() =>
  state.goals.map((goal) => ({
    ...goal,
    progressRate:
      goal.targetAmount > 0 ? (positiveAmount(goal.currentAmount) / goal.targetAmount) * 100 : 0,
  })),
)

const budgetUsage = computed(() =>
  state.budgets.map((budget) => {
    const spent = monthlyTransactions.value
      .filter(
        (transaction) =>
          transaction.categoryId === budget.categoryId &&
          (transaction.type === 'expense' || transaction.type === 'fee'),
      )
      .reduce((total, transaction) => total + positiveAmount(transaction.amount), 0)

    return {
      ...budget,
      categoryName: categoryName(budget.categoryId),
      spent,
      usageRate: budget.limitAmount > 0 ? (spent / budget.limitAmount) * 100 : 0,
    }
  }),
)

function addAccount(account: Omit<Account, 'id'>): void {
  state.accounts.push({ ...account, id: createId('acc') })
}

function addCreditCard(card: Omit<CreditCard, 'id'>): void {
  state.creditCards.push({ ...card, id: createId('card') })
}

function addTransaction(input: TransactionInput): void {
  const transaction: Transaction = {
    ...input,
    id: createId('trx'),
    amount: positiveAmount(input.amount),
    tags: input.tags.filter(Boolean),
  }

  state.transactions.unshift(transaction)
  applyTransactionEffects(transaction)
}

function addBudget(budget: Omit<Budget, 'id'>): void {
  state.budgets.push({ ...budget, id: createId('bud') })
}

function addGoal(goal: Omit<Goal, 'id'>): void {
  state.goals.push({ ...goal, id: createId('goal') })
}

export function useFinanceStore() {
  return {
    state,
    currentMonth,
    metrics,
    categoryExpenses,
    monthlyCashflow,
    recentTransactions,
    creditCardUsage,
    goalsProgress,
    budgetUsage,
    addAccount,
    addCreditCard,
    addTransaction,
    addBudget,
    addGoal,
    getSnapshot,
    persistFinanceState,
    accountName,
    categoryName,
    merchantName,
    cardName,
  }
}
