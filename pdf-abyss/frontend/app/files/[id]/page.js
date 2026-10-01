import { API_URL, safeGet } from "../../../lib/api";

export const runtime = "edge";
export const dynamic = "force-dynamic";

export default async function FilePage({ params }) {
  const { id } = await params;
  const { data: file, error, status } = await safeGet(`/files/${encodeURIComponent(id)}`);

  if (!file) {
    return (
      <div className="empty">
        {status === 404 ? "File not found." : `Could not load this file (${error}).`}
        <div style={{ marginTop: 12 }}><a href="/">&larr; Back to library</a></div>
      </div>
    );
  }

  return (
    <div className="panel">
      <a href="/">&larr; Back</a>
      <h1 style={{ marginBottom: 6 }}>{file.title}</h1>
      <span className="badge ok">{file.status}</span>
      <span className="badge">{file.category?.name || "Uncategorized"}</span>
      {file.description && <p>{file.description}</p>}
      <dl className="kv">
        {file.document_type && (<><dt>Type</dt><dd>{file.document_type}</dd></>)}
        {file.institution && (<><dt>Institution</dt><dd>{file.institution}</dd></>)}
        {file.year && (<><dt>Year</dt><dd>{file.year}</dd></>)}
        {file.license && (<><dt>License</dt><dd>{file.license}</dd></>)}
        <dt>Size</dt><dd>{(file.file_size / 1024 / 1024).toFixed(2)} MB</dd>
      </dl>
      <a className="btn" href={`${API_URL}/files/${file.id}/download`}>Download PDF</a>
    </div>
  );
}
