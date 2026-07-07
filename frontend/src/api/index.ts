export interface FileItem {
  hash: string
  name: string
  path?: string
  mime?: string
}

export interface Song {
  name: string
  path: string
  mime?: string
}

export interface Course {
  id: number
  name: string
}

export interface FinanceSyncPayload {
  syncedAt: string
  data: unknown
}

const isLocalHost = (hostname: string): boolean =>
  hostname === 'localhost' || hostname === '127.0.0.1'

const toApiUrl = (path: string): string => {
  const configuredBase = import.meta.env.VITE_API_BASE_URL?.trim()
  const origin = configuredBase || window.location.origin
  const url = new URL(path, origin)

  if (url.protocol !== 'https:' && !isLocalHost(url.hostname)) {
    url.protocol = 'https:'
  }

  return url.toString()
}

async function requestFiles(): Promise<FileItem[] | false> {
  const path = import.meta.env.VITE_API_FILES_URL?.trim() || '/files'
  const url = toApiUrl(path)

  const response = await fetch(url)

  if (!response.ok) {
    return false
  }

  const payload = await response.json().catch(() => [])

  return payload.map((value: Record<string, unknown>) => {
    return {
      hash: value?.hash,
      name: value?.name,
      path: value?.path,
    }
  })
}

async function requestFile(hash: string): Promise<unknown | false> {
  const path = import.meta.env.VITE_API_FILES_URL?.trim() || '/file'
  const params = new URLSearchParams({ hash })
  const url = toApiUrl(`${path}?${params}`)

  const response = await fetch(url)

  if (!response.ok) {
    return false
  }

  return await response.blob()
}

async function requestMusic(): Promise<Song[] | false> {
  const path = import.meta.env.VITE_API_MUSIC_URL?.trim() || '/music'
  const url = toApiUrl(path)

  const response = await fetch(url)

  if (!response.ok) {
    return false
  }

  const payload = await response.json().catch(() => [])

  return payload.map((value: Record<string, unknown>) => ({
    name: String(value?.name || ''),
    path: String(value?.path || ''),
    mime: value?.mime ? String(value.mime) : undefined,
  }))
}

async function upload(
  data: FormData,
  onUploadProgress?: (progressEvent: { loaded: number; total?: number }) => void,
): Promise<boolean> {
  const path = import.meta.env.VITE_API_FILES_URL?.trim() || '/file'
  const url = toApiUrl(path)

  return await new Promise((resolve) => {
    const request = new XMLHttpRequest()

    request.open('POST', url)

    request.upload.onprogress = (event) => {
      onUploadProgress?.({
        loaded: event.loaded,
        total: event.lengthComputable ? event.total : undefined,
      })
    }

    request.onload = () => {
      resolve(request.status >= 200 && request.status < 300)
    }

    request.onerror = () => {
      resolve(false)
    }

    request.send(data)
  })
}

async function screenOff(): Promise<boolean> {
  const path = import.meta.env.VITE_API_SCREEN_URL?.trim() || '/screen'
  const url = toApiUrl(path)

  const response = await fetch(url, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ mode: 'off' }),
  })

  if (!response.ok) {
    return false
  }

  return true
}

async function saveNote(name: string, value: string): Promise<boolean> {
  const path = import.meta.env.VITE_API_SCREEN_URL?.trim() || '/notes'
  const url = toApiUrl(path)

  const response = await fetch(url, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ name, value }),
  })

  if (!response.ok) {
    return false
  }

  return true
}

async function syncFinanceData(data: unknown): Promise<boolean> {
  const path = import.meta.env.VITE_API_FINANCE_SYNC_URL?.trim() || '/finance/sync'
  const url = toApiUrl(path)

  const payload: FinanceSyncPayload = {
    syncedAt: new Date().toISOString(),
    data,
  }

  const response = await fetch(url, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify(payload),
  })

  return response.ok
}
/*
async function requestCurses(): Promise<AxiosResponse<string[]> | false> {
  try {
    return await axios.get<string[]>('/curses')
  } catch (error) {
    console.error(error)
    return false
  }
}

async function requestMusic(): Promise<AxiosResponse<Song[]> | false> {
  try {
    return await axios.get<Song[]>('/music')
  } catch (error) {
    console.error(error)
    return false
  }
}

async function upload(
  data: FormData,
  onUploadProgress?: (progressEvent: AxiosProgressEvent) => void,
): Promise<AxiosResponse | false> {
  try {
    return await axios.post('/file', data, {
      headers: {
        'Content-Type': 'multipart/form-data',
      },
      onUploadProgress,
    })
  } catch (error) {
    console.error(error)
    return false
  }
}





axios.interceptors.request.use((config: InternalAxiosRequestConfig) => config)
*/
const api = {
  requestFiles,
  requestFile,
  requestMusic,
  upload,
  saveNote,
  syncFinanceData,
  screenOff,
}

export default api
