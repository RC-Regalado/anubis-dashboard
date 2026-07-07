import { computed, reactive } from 'vue'

export type WorkoutType = 'strength' | 'cardio'
export type MealType = 'breakfast' | 'lunch' | 'dinner' | 'snack'

export interface DayLog {
  id: string
  date: string
  weight: number
  waist: number
  chest: number
  thigh: number
  sleepHours: number
  sleepQuality: number
  bedtime: string
  wakeTime: string
  nightlyWakeups: number
  wakeEnergy: number
  energy: number
  stress: number
  doms: number
  generalPain: number
  specificPain: string
  motivation: number
  waterLiters: number
  calories: number
  protein: number
  simpleSugar: number
  fastingHours: number
  steps: number
  distanceKm: number
  activeMinutes: number
  restingHeartRate: number
  recoveryHeartRate: number
  bloodPressureSystolic: number
  bloodPressureDiastolic: number
  note: string
}

export interface WorkoutLog {
  id: string
  date: string
  type: WorkoutType
  durationMinutes: number
  intensityRpe: number
  averageHeartRate: number
  maxHeartRate: number
  restMinutes: number
}

export interface ExerciseLog {
  id: string
  workoutId: string
  exercise: string
  weight: number
  reps: number
  sets: number
}

export interface MealLog {
  id: string
  date: string
  type: MealType
  protein: number
  carbs: number
  fats: number
}

export interface Habit {
  id: string
  name: string
  target: string
  streak: number
  completedToday: boolean
}

interface UtilsState {
  days: DayLog[]
  workouts: WorkoutLog[]
  exercises: ExerciseLog[]
  meals: MealLog[]
  habits: Habit[]
}

export type DayInput = Omit<DayLog, 'id'>
export type WorkoutInput = Omit<WorkoutLog, 'id'>
export type ExerciseInput = Omit<ExerciseLog, 'id'>
export type MealInput = Omit<MealLog, 'id'>
export type HabitInput = Omit<Habit, 'id' | 'streak' | 'completedToday'>

const state = reactive<UtilsState>({
  days: [
    {
      id: 'day-2026-04-21',
      date: '2026-04-21',
      weight: 82.4,
      waist: 91,
      chest: 103,
      thigh: 58,
      sleepHours: 6.6,
      sleepQuality: 3,
      bedtime: '23:35',
      wakeTime: '06:10',
      nightlyWakeups: 2,
      wakeEnergy: 3,
      energy: 3,
      stress: 4,
      doms: 3,
      generalPain: 2,
      specificPain: 'Piriforme leve',
      motivation: 4,
      waterLiters: 2.4,
      calories: 2280,
      protein: 148,
      simpleSugar: 42,
      fastingHours: 13,
      steps: 7200,
      distanceKm: 5.2,
      activeMinutes: 62,
      restingHeartRate: 62,
      recoveryHeartRate: 34,
      bloodPressureSystolic: 118,
      bloodPressureDiastolic: 76,
      note: 'Dia pesado de trabajo',
    },
    {
      id: 'day-2026-04-22',
      date: '2026-04-22',
      weight: 82.1,
      waist: 90.7,
      chest: 103,
      thigh: 58,
      sleepHours: 7.2,
      sleepQuality: 4,
      bedtime: '22:55',
      wakeTime: '06:05',
      nightlyWakeups: 1,
      wakeEnergy: 4,
      energy: 4,
      stress: 3,
      doms: 2,
      generalPain: 1,
      specificPain: '',
      motivation: 4,
      waterLiters: 3,
      calories: 2140,
      protein: 156,
      simpleSugar: 28,
      fastingHours: 14,
      steps: 9400,
      distanceKm: 6.8,
      activeMinutes: 84,
      restingHeartRate: 59,
      recoveryHeartRate: 38,
      bloodPressureSystolic: 116,
      bloodPressureDiastolic: 74,
      note: 'Mejor descanso',
    },
    {
      id: 'day-2026-04-23',
      date: '2026-04-23',
      weight: 82,
      waist: 90.4,
      chest: 103.2,
      thigh: 58.3,
      sleepHours: 7.5,
      sleepQuality: 4,
      bedtime: '22:45',
      wakeTime: '06:15',
      nightlyWakeups: 1,
      wakeEnergy: 4,
      energy: 4,
      stress: 2,
      doms: 3,
      generalPain: 2,
      specificPain: 'Piriforme post-sentadilla',
      motivation: 5,
      waterLiters: 2.8,
      calories: 2210,
      protein: 162,
      simpleSugar: 34,
      fastingHours: 13.5,
      steps: 8400,
      distanceKm: 6.1,
      activeMinutes: 78,
      restingHeartRate: 58,
      recoveryHeartRate: 40,
      bloodPressureSystolic: 115,
      bloodPressureDiastolic: 73,
      note: '',
    },
    {
      id: 'day-2026-04-24',
      date: '2026-04-24',
      weight: 81.8,
      waist: 90.3,
      chest: 103.2,
      thigh: 58.4,
      sleepHours: 6.1,
      sleepQuality: 2,
      bedtime: '00:10',
      wakeTime: '06:20',
      nightlyWakeups: 3,
      wakeEnergy: 2,
      energy: 2,
      stress: 5,
      doms: 4,
      generalPain: 3,
      specificPain: 'Piriforme',
      motivation: 3,
      waterLiters: 2.1,
      calories: 2450,
      protein: 132,
      simpleSugar: 68,
      fastingHours: 11,
      steps: 5100,
      distanceKm: 3.7,
      activeMinutes: 42,
      restingHeartRate: 65,
      recoveryHeartRate: 29,
      bloodPressureSystolic: 123,
      bloodPressureDiastolic: 80,
      note: 'Alto estres y sedentarismo',
    },
    {
      id: 'day-2026-04-25',
      date: '2026-04-25',
      weight: 81.7,
      waist: 90.1,
      chest: 103.4,
      thigh: 58.2,
      sleepHours: 7.8,
      sleepQuality: 5,
      bedtime: '22:25',
      wakeTime: '06:15',
      nightlyWakeups: 0,
      wakeEnergy: 5,
      energy: 5,
      stress: 2,
      doms: 2,
      generalPain: 1,
      specificPain: '',
      motivation: 5,
      waterLiters: 3.2,
      calories: 2160,
      protein: 170,
      simpleSugar: 24,
      fastingHours: 15,
      steps: 10200,
      distanceKm: 7.4,
      activeMinutes: 96,
      restingHeartRate: 57,
      recoveryHeartRate: 42,
      bloodPressureSystolic: 114,
      bloodPressureDiastolic: 72,
      note: 'Buen dia',
    },
  ],
  workouts: [
    {
      id: 'wrk-1',
      date: '2026-04-22',
      type: 'strength',
      durationMinutes: 68,
      intensityRpe: 8,
      averageHeartRate: 128,
      maxHeartRate: 168,
      restMinutes: 16,
    },
    {
      id: 'wrk-2',
      date: '2026-04-23',
      type: 'strength',
      durationMinutes: 74,
      intensityRpe: 9,
      averageHeartRate: 132,
      maxHeartRate: 172,
      restMinutes: 19,
    },
    {
      id: 'wrk-3',
      date: '2026-04-25',
      type: 'cardio',
      durationMinutes: 42,
      intensityRpe: 7,
      averageHeartRate: 142,
      maxHeartRate: 164,
      restMinutes: 6,
    },
  ],
  exercises: [
    { id: 'exe-1', workoutId: 'wrk-1', exercise: 'Sentadilla', weight: 105, reps: 5, sets: 4 },
    { id: 'exe-2', workoutId: 'wrk-1', exercise: 'Press banca', weight: 82.5, reps: 6, sets: 4 },
    { id: 'exe-3', workoutId: 'wrk-2', exercise: 'Peso muerto', weight: 140, reps: 4, sets: 3 },
    { id: 'exe-4', workoutId: 'wrk-2', exercise: 'Remo barra', weight: 75, reps: 8, sets: 4 },
  ],
  meals: [
    { id: 'meal-1', date: '2026-04-22', type: 'breakfast', protein: 36, carbs: 58, fats: 18 },
    { id: 'meal-2', date: '2026-04-22', type: 'lunch', protein: 54, carbs: 82, fats: 24 },
    { id: 'meal-3', date: '2026-04-25', type: 'dinner', protein: 62, carbs: 74, fats: 20 },
  ],
  habits: [
    { id: 'habit-water', name: 'Agua 3L', target: '3 litros', streak: 4, completedToday: true },
    { id: 'habit-walk', name: 'Caminar', target: '8000 pasos', streak: 3, completedToday: true },
    { id: 'habit-mobility', name: 'Movilidad cadera', target: '10 min', streak: 2, completedToday: false },
  ],
})

function createId(prefix: string): string {
  return `${prefix}-${Date.now()}-${Math.random().toString(36).slice(2, 7)}`
}

function average(values: number[]): number {
  const valid = values.filter((value) => Number.isFinite(value) && value > 0)
  if (!valid.length) return 0
  return valid.reduce((total, value) => total + value, 0) / valid.length
}

function lastItems<T extends { date: string }>(items: T[], count = 7): T[] {
  return [...items].sort((left, right) => right.date.localeCompare(left.date)).slice(0, count)
}

const recentDays = computed(() => lastItems(state.days, 7).reverse())
const latestDay = computed(() => [...state.days].sort((left, right) => right.date.localeCompare(left.date))[0])

const metrics = computed(() => {
  const days = recentDays.value
  const latest = latestDay.value
  const trainingDays = new Set(state.workouts.map((workout) => workout.date)).size
  const trackedDays = Math.max(state.days.length, 1)
  const firstWaist = days[0]?.waist ?? 0
  const lastWaist = days.at(-1)?.waist ?? firstWaist

  return {
    weeklyAverageWeight: average(days.map((day) => day.weight)),
    waistTrend: lastWaist - firstWaist,
    averageRecoveryHeartRate: average(days.map((day) => day.recoveryHeartRate)),
    averageRestingHeartRate: average(days.map((day) => day.restingHeartRate)),
    averageSleepHours: average(days.map((day) => day.sleepHours)),
    trainingConsistency: (trainingDays / trackedDays) * 100,
    averageEnergy: average(days.map((day) => day.energy)),
    averageStress: average(days.map((day) => day.stress)),
    averageDoms: average(days.map((day) => day.doms)),
    averageCalories: average(days.map((day) => day.calories)),
    averageProtein: average(days.map((day) => day.protein)),
    averageSugar: average(days.map((day) => day.simpleSugar)),
    averageWater: average(days.map((day) => day.waterLiters)),
    averageSteps: average(days.map((day) => day.steps)),
    latestWeight: latest?.weight ?? 0,
    latestBloodPressure: latest
      ? `${latest.bloodPressureSystolic}/${latest.bloodPressureDiastolic}`
      : '-',
  }
})

const workoutVolumeByExercise = computed(() =>
  state.exercises
    .map((exercise) => ({
      ...exercise,
      volume: exercise.weight * exercise.reps * exercise.sets,
    }))
    .sort((left, right) => right.volume - left.volume),
)

const subjectiveLoad = computed(() =>
  recentDays.value.map((day) => ({
    date: day.date,
    energy: day.energy,
    stress: day.stress,
    doms: day.doms,
    pain: day.generalPain,
    motivation: day.motivation,
  })),
)

const relationships = computed(() => {
  const latest = latestDay.value
  const insights: Array<{ label: string; value: string; tone: 'good' | 'warn' | 'neutral' }> = []

  if (!latest) return insights

  insights.push({
    label: 'Sueno - rendimiento',
    value:
      metrics.value.averageSleepHours >= 7
        ? 'Base de recuperacion estable'
        : 'Sueno bajo: observar caida de RPE o volumen',
    tone: metrics.value.averageSleepHours >= 7 ? 'good' : 'warn',
  })

  insights.push({
    label: 'Calorias - peso - cintura',
    value:
      metrics.value.waistTrend <= 0 && metrics.value.averageCalories < 2300
        ? 'Deficit con cintura bajando'
        : 'Revisar retencion, sodio o adherencia',
    tone: metrics.value.waistTrend <= 0 ? 'good' : 'warn',
  })

  insights.push({
    label: 'Cardio - FC - recuperacion',
    value:
      metrics.value.averageRecoveryHeartRate >= 35
        ? 'Recuperacion cardiovascular positiva'
        : 'FCR baja: priorizar descanso y zona 2',
    tone: metrics.value.averageRecoveryHeartRate >= 35 ? 'good' : 'warn',
  })

  insights.push({
    label: 'Estres - dolor - lesiones',
    value:
      latest.stress >= 4 && latest.specificPain
        ? `${latest.specificPain}: combinar movilidad y pausas activas`
        : 'Sin alerta fuerte de dolor especifico',
    tone: latest.stress >= 4 && latest.specificPain ? 'warn' : 'neutral',
  })

  insights.push({
    label: 'Azucar - energia',
    value:
      latest.simpleSugar > 55 && latest.energy <= 3
        ? 'Posible pico y caida energetica'
        : 'Energia compatible con alimentacion',
    tone: latest.simpleSugar > 55 && latest.energy <= 3 ? 'warn' : 'good',
  })

  return insights
})

function addDay(input: DayInput): void {
  const index = state.days.findIndex((day) => day.date === input.date)
  const next = { ...input, id: index >= 0 ? state.days[index]!.id : createId('day') }

  if (index >= 0) {
    state.days[index] = next
    return
  }

  state.days.push(next)
}

function addWorkout(input: WorkoutInput, exercises: Array<Omit<ExerciseInput, 'workoutId'>>): void {
  const workoutId = createId('wrk')
  state.workouts.push({ ...input, id: workoutId })
  exercises
    .filter((exercise) => exercise.exercise.trim())
    .forEach((exercise) => {
      state.exercises.push({ ...exercise, workoutId, id: createId('exe') })
    })
}

function addMeal(input: MealInput): void {
  state.meals.push({ ...input, id: createId('meal') })
}

function addHabit(input: HabitInput): void {
  state.habits.push({ ...input, id: createId('habit'), streak: 0, completedToday: false })
}

function toggleHabit(id: string): void {
  const habit = state.habits.find((item) => item.id === id)
  if (!habit) return

  habit.completedToday = !habit.completedToday
  habit.streak = Math.max(0, habit.streak + (habit.completedToday ? 1 : -1))
}

export function useUtilsStore() {
  return {
    state,
    latestDay,
    metrics,
    recentDays,
    workoutVolumeByExercise,
    subjectiveLoad,
    relationships,
    addDay,
    addWorkout,
    addMeal,
    addHabit,
    toggleHabit,
  }
}
