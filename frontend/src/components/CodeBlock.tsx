type Props = {
  code: string;
};

export function CodeBlock({ code }: Props) {
  return <pre className="code-block">{code}</pre>;
}