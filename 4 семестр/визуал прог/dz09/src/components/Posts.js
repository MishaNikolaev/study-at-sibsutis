import DataApp from './DataApp';
import * as Yup from 'yup';

const Posts = () => {
  const initialValues = {
    userId: '',
    title: '',
    body: ''
  };

  const validationSchema = Yup.object({
    userId: Yup.number().required('User ID is required'),
    title: Yup.string().required('Title is required'),
    body: Yup.string().required('Body is required')
  });

  const fields = [
    { name: 'userId', label: 'User ID', type: 'number' },
    { name: 'title', label: 'Title' },
    { name: 'body', label: 'Body', as: 'textarea' }
  ];

  return (
    <DataApp
      endpoint="posts"
      initialValues={initialValues}
      validationSchema={validationSchema}
      fields={fields}
    />
  );
};

export default Posts;
