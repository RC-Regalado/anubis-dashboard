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
  saveNote,
  screenOff,
}

export default api
